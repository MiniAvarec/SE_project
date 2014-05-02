#include "mainmenudialog.h"
#include "ui_mainmenudialog.h"
#include <QDebug>
#include "couriersmanagementdialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QMessageBox>
#include <QMap>
#include <QVariant>
#include <QVBoxLayout>
#include "staff.h"
#include "ui_staff.h"
#include "product.h"
#include "addproductdialog.h"
#include "ui_addproductdialog.h"
#include "addstaffdialog.h"
#include "ui_addstaffdialog.h"
#include <ctime>
#include <QTimer>
#include "addpromoandgallerydialog.h"
#include "ui_addpromoandgallerydialog.h"
#include <QStatusBar>

MainMenuDialog::MainMenuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenuDialog)
{

    ui->setupUi(this);

    setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint|Qt::WindowCloseButtonHint);
    showMaximized();
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->showFullScreen();

    backButton = new QPushButton("Назад");

    connect(backButton, SIGNAL(clicked()), this, SLOT(backButton_clicked()));
    backButton->setHidden(true);
    ui->horizontalLayout->insertWidget(0, backButton);

    connect(ui->stackedWidget, &QStackedWidget::currentChanged, [=](int i)
    {
        if(i==MAIN_MENU)
            backButton->setHidden(true);
        else
        {
            backButton->setHidden(false);
        }
    });

    //timer for updating the table orders
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]()
    {
        if(ui->stackedWidget->currentIndex()==MANAGER_ORDERS_MANAGEMENT ||
                ui->stackedWidget->currentIndex()==ADMIN_ORDERS_VIEW)
            on_ordersBtn_clicked();
    });
    timer->start(1000*30);
}

MainMenuDialog::~MainMenuDialog()
{
    delete ui;
}

void MainMenuDialog::on_ordersBtn_clicked()
{
    qDebug() << "Update";
    if(!db.isOpen())
        if(!db.open())
        {
            QMessageBox::warning(this, "Ошибка", "БД не открыта<br>"+
                                            db.lastError().text());
            return;
        }
    //QString sql="SELECT * FROM `order` ORDER BY `id` ASC;";
    // Запрос с именами курьеров, там где они назначены на заказы
    QString sql="SELECT `order`.*, `staff`.name AS curname FROM `order` LEFT JOIN (`staff`) ON (`staff`.id=`order`.staff_id) ORDER BY `order`.id ASC;";
    QSqlQuery q(db);
    if(isAdmin)
    {
        ui->stackedWidget->setCurrentIndex(ADMIN_ORDERS_VIEW);
        ui->adminOrderTable->clear();

        if(q.exec(sql))
        {
            while(q.next())
            {
                qDebug() << "Record";
                //set the header labels
                if(q.at()==0)// first record
                {
                    QSqlRecord r = q.record();
                    ui->adminOrderTable->setRowCount(q.size());
                    ui->adminOrderTable->setColumnCount(r.count());
                    QStringList labels;
                    for(int i=0; i<r.count(); i++)
                    {
                        labels.append(r.fieldName(i));
                        qDebug() << "field name: " << r.fieldName(i);
                    }
                    qDebug() << "labels.count() = " << labels.count();
                    ui->adminOrderTable->setHorizontalHeaderLabels(labels);
                    ui->adminOrderTable->resizeRowsToContents();

                }

                QSqlRecord rec = q.record();
                for(int i=0; i<rec.count(); i++)
                {
                    QTableWidgetItem *item = new QTableWidgetItem;
                    if(rec.fieldName(i)=="status")
                    {
                        int s = rec.value(i).toInt();
                        item->setText(OrderStatuses::getText(s));
                        item->setBackgroundColor(OrderStatuses::getColor(s));
                    }
                    else
                    {
                        item->setText(rec.value(i).toString());
                    }

                    ui->adminOrderTable->setItem(q.at(), i, item);
                    ui->adminOrderTable->resizeRowsToContents();

                }
                //fill managerOrder table
            }
        }
        else
            qDebug() << q.lastError().text();
        db.close();
    }
    else // for manager
    {
        ui->stackedWidget->setCurrentIndex(MANAGER_ORDERS_MANAGEMENT);
        ui->managerOrderTable->clear();
        if(q.exec(sql))
        {
            while(q.next())
            {
                qDebug() << "Record";
                //set the header labels
                if(q.at()==0)// first record
                {
                    QSqlRecord r = q.record();
                    ui->managerOrderTable->setRowCount(q.size());
                    ui->managerOrderTable->setColumnCount(13);
                    QStringList labels;
                    labels << "ID" << "Name" << "Surname" << "Address" << "Phone"
                              << "Change" << "Extra" << "Orders" << "Count of orders"
                                 << "Total" << "Courier";
                    /*for(int i=0; i<r.count(); i++)
                    {
                        if(r.fieldName(i)!="status")
                            labels.append(r.fieldName(i));
                    }*/
                    qDebug() << "labels.count() = " << labels.count();
                    ui->managerOrderTable->setHorizontalHeaderLabels(labels);
                    ui->managerOrderTable->setColumnHidden(0, true);
                }

                QSqlRecord rec = q.record();
                ui->managerOrderTable->setItem(q.at(), 0, new QTableWidgetItem(rec.value("id").toString()));
                ui->managerOrderTable->setItem(q.at(), 1, new QTableWidgetItem(rec.value("name").toString()));
                ui->managerOrderTable->setItem(q.at(), 2, new QTableWidgetItem(rec.value("surname").toString()));
                ui->managerOrderTable->setItem(q.at(), 3, new QTableWidgetItem(rec.value("address").toString()));
                ui->managerOrderTable->setItem(q.at(), 4, new QTableWidgetItem(rec.value("tel").toString()));
                ui->managerOrderTable->setItem(q.at(), 5, new QTableWidgetItem(rec.value("change").toString()));
                ui->managerOrderTable->setItem(q.at(), 6, new QTableWidgetItem(rec.value("extra").toString()));
                ui->managerOrderTable->setItem(q.at(), 7, new QTableWidgetItem(rec.value("orders").toString()));
                ui->managerOrderTable->setItem(q.at(), 8, new QTableWidgetItem(rec.value("count_of_orders").toString()));
                ui->managerOrderTable->setItem(q.at(), 9, new QTableWidgetItem(rec.value("total").toString()));
                ui->managerOrderTable->setItem(q.at(), 10,new QTableWidgetItem(rec.value("curname").toString()));

                ui->managerOrderTable->resizeRowsToContents();
//                ui->managerOrderTable->resizeColumnToContents(7);

//              ui->managerOrderTable->columnWidth
                QTableWidgetItem *item = new QTableWidgetItem("Принять");
                QTableWidgetItem *item2 = new QTableWidgetItem("Отклонить");

                int status = rec.value("status").toInt();
                if(status==OrderStatuses::ACCEPTED)
                {
                    item->setText(OrderStatuses::getText(OrderStatuses::ACCEPTED));
                    item->setBackgroundColor(OrderStatuses::getColor(status));
                }
                else if(status==OrderStatuses::CANCELED)
                {
                    item2->setText(OrderStatuses::getText(OrderStatuses::CANCELED));
                    item2->setBackgroundColor(OrderStatuses::getColor(status));
                }
                ui->managerOrderTable->setItem(q.at(), 11, item);
                ui->managerOrderTable->setItem(q.at(), 12, item2);
            }
        }
        else
            qDebug() << q.lastError().text();
        db.close();
    }
}

void MainMenuDialog::backButton_clicked()
{
    switch(ui->stackedWidget->currentIndex())
    {
        case MANAGER_ORDERS_MANAGEMENT:
        case ADMIN_ORDERS_VIEW:
        case DELIVERY_VIEW:
        case CONTENT_MANAGEMENT:
        case MANAGER_STAFF:
        case PROMOTIONS_MANAGEMENT:
        case GALLERY_MANAGEMENT:
        case ADMIN_STAFF:
            ui->stackedWidget->setCurrentIndex(MAIN_MENU);
        break;
    }
    QProcess p;
    p.start("taskkill /IM osk.exe");
    p.waitForFinished();

}

void MainMenuDialog::on_deliveryBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(DELIVERY_VIEW);
    ui->deliveryViewTable->clear();
    if(!db.isOpen()) db.open();
    QSqlQuery q(db);
    QString sql = "SELECT `staff`.*, `courier`.status FROM `staff` LEFT JOIN `courier` ON (`courier`.staff_id=`staff`.id) WHERE `staff`.position='Courier';";
    if(q.exec(sql))
    {
        ui->deliveryViewTable->setRowCount(q.size());
        while(q.next())
        {
            QSqlRecord rec = q.record();
            //set the header labels
            if(q.at()==0)
            {
                QStringList labels;
                labels << "Имя" << "Состояние";// << "Адрес доставки" << "Время заказа";
                ui->deliveryViewTable->setColumnCount(2);
                ui->deliveryViewTable->setHorizontalHeaderLabels(labels);
            }
            // set the fields

            ui->deliveryViewTable->setItem(q.at(), 0, new QTableWidgetItem(rec.value("name").toString()));

            int status = rec.value("status").toInt();
            QTableWidgetItem* item;
            if(status==0)
                item = new QTableWidgetItem("Свободен");
            else
                item = new QTableWidgetItem("Занят");
            ui->deliveryViewTable->setItem(q.at(), 1, item);
        }
    }
}

void MainMenuDialog::on_personalBtn_clicked()
{
    if(!db.isOpen())
        if(!db.open())
        {
            QMessageBox::warning(this, "Ошибка",
                                 "БД не открыта<br>"+db.lastError().text());
            return;
        }

    QString sql = QString("SELECT * FROM `staff` WHERE `position`!='Administrator';");
    QSqlQuery q(db);

    if(isAdmin)
    {
        ui->stackedWidget->setCurrentIndex(ADMIN_STAFF);
        delete ui->adminStaffScrollArea->widget();

        if(q.exec(sql))
        {
            QWidget* w = new QWidget;
            //QVBoxLayout* lay = new QVBoxLayout;
            QGridLayout* lay = new QGridLayout;
            w->setLayout(lay);
            //w->resize(350,q.size()*140);
            w->resize(ui->stackedWidget->width(),q.size()*140);

            while(q.next())
            {
                Staff* p = new Staff;
                connect(p, &Staff::editClicked, [=](int i)
                {
                    if(!db.isOpen()) db.open();
                    QSqlQuery q(db);
                    if(q.exec(QString("SELECT * FROM `staff` WHERE `id`=%1").arg(i)))
                    {
                        if(q.first())
                        {
                            AddStaffDialog* dlg=new AddStaffDialog(this);
                            dlg->ui->staffNameEdit->setText(q.value("name").toString());
                            dlg->ui->staffEmailEdit->setText(q.value("email").toString());
                            dlg->ui->staffPositionCombo->setCurrentText(q.value("position").toString());
                            dlg->id=q.value(0).toInt();
                            dlg->imageData = q.value("foto").toByteArray();
                            if(dlg->exec()==QDialog::Accepted)
                            {
                               qDebug() << "Staff: save the record..." << q.value("name");
                               if(!db.isOpen()) db.open();
                               QSqlQuery q(db);
                               q.prepare("UPDATE `staff` SET "
                                         "`name`=:name,"
                                         "`email`=:email,"
                                         "`position`=:position,"
                                         "`foto`=:foto WHERE `id`="+QString::number(dlg->id)+";");
                               q.bindValue(":name",dlg->ui->staffNameEdit->text());
                               q.bindValue(":email",dlg->ui->staffEmailEdit->text());
                               q.bindValue(":position",dlg->ui->staffPositionCombo->currentText());
                               q.bindValue(":foto",dlg->imageData);

                               if(q.exec())
                               {
                                   QMessageBox::information(this,"Запись сохранена","Запись сохранена!");
                                   on_personalBtn_clicked();

                               }
                               else
                                   QMessageBox::warning(this,"Ошибка","Запись не сохранена");
                            }
                            dlg->deleteLater();

                        }
                    }
                    else
                        qDebug() << q.lastError().text();

                });
                connect(p, &Staff::delClicked, [=](int i)
                {
                    if(!db.isOpen()) db.open();
                    QSqlQuery q(db);
                    if(q.exec(QString("DELETE FROM `staff` WHERE `id`=%1").arg(i)))
                    {
                        QMessageBox::information(this, "Удалено", "Запись удалена");
                        on_personalBtn_clicked();
                    }
                    else
                        QMessageBox::information(this, "Ошибка", "Запись не удалена");

                });
                p->setForAdmin();
                p->id = q.value(0).toInt();
                p->ui->nameLabel->setText(q.value("name").toString());
                p->ui->positionLabel->setText(q.value("position").toString());
                p->setPhoto(q.value("foto").toByteArray());
                lay->addWidget(p);
            }
            ui->adminStaffScrollArea->setWidget(w);
        }
        else
            qDebug() << q.lastError().text();
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(MANAGER_STAFF);
        delete ui->managerStaffScrollArea->widget();



        if(q.exec(sql))
        {
            QWidget* w = new QWidget;
            QVBoxLayout* lay = new QVBoxLayout;
            w->setLayout(lay);
            w->resize(350,q.size()*140);
            while(q.next())
            {
                Staff* p = new Staff;
                p->ui->nameLabel->setText(q.value("name").toString());
                p->ui->positionLabel->setText(q.value("position").toString());
                p->setPhoto(q.value("foto").toByteArray());
                lay->addWidget(p);
            }
            ui->managerStaffScrollArea->setWidget(w);
        }
        else
            qDebug() << q.lastError().text();
    }
    db.close();
}

void MainMenuDialog::on_contentBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(CONTENT_MANAGEMENT);

    delete ui->contentScrollArea->widget();
    if(!db.isOpen()) db.open();
    QSqlQuery q(db);
    QString sql = QString("SELECT * FROM `content`;");


    if(q.exec(sql))
    {
        QWidget *w = new QWidget;
        QVBoxLayout* lay = new QVBoxLayout;
        w->setLayout(lay);
        while(q.next())
        {
            Product* p = new Product;
            connect(p, &Product::editClicked, [=](int i)
            {
                if(!db.isOpen()) db.open();
                QSqlQuery q(db);
                if(q.exec(QString("SELECT * FROM content WHERE `id`=%1").arg(i)))
                {
                    if(q.first())
                    {
                        AddProductDialog *dlg = new AddProductDialog(this);
                        dlg->ui->addBtn->setText("Сохранить");
                        dlg->ui->productTypeEdit->setText(q.value("type").toString());
                        dlg->ui->productNameEdit->setText(q.value("name").toString());
                        dlg->ui->productCostEdit->setText(q.value("price").toString());
                        dlg->ui->productContentEdit->setText(q.value("ingredient").toString());
                        dlg->id = q.value(0).toInt();
                        dlg->imageData = q.value("foto").toByteArray();

                        if(dlg->exec()==QDialog::Accepted)
                        {
                            QSqlQuery q(db);
                            q.prepare("UPDATE `content` SET "
                                      "`type`=:type,"
                                      "`name`=:name,"
                                      "`price`=:price,"
                                      "`ingredient`=:ingredient,"
                                      "`foto`=:foto WHERE `id`="+QString::number(dlg->id)+";");
                            q.bindValue(":type",dlg->ui->productTypeEdit->text());
                            q.bindValue(":name",dlg->ui->productNameEdit->text());
                            q.bindValue(":price",dlg->ui->productCostEdit->text());
                            q.bindValue(":ingredient",dlg->ui->productContentEdit->text());
                            q.bindValue(":foto",dlg->imageData);

                            if(q.exec())
                            {
                                QMessageBox::information(this, "Продукт сохранен", "Продукт сохранен");
                                on_contentBtn_clicked();
                            }
                            else
                                QMessageBox::warning(this, "Ошибка", "Продукт не сохранен");
                        }
                    }
                }

            });
            connect(p, &Product::delClicked, [=](int i)
            {
                QSqlQuery q(db);
                if(q.exec(QString("DELETE FROM `content` WHERE `id`=%1;").arg(i)))
                {
                    QMessageBox::information(this, "Продукт удален", "Продукт удален");
                }else
                QMessageBox::warning(this, "Ошибка", "Продукт не удален");
            });
            p->setId(q.value(0).toInt());
            p->setProductName(q.value("name").toString());
            p->setProductDescription(q.value("ingredient").toString());
            p->setProductPhoto(q.value("foto").toByteArray());
            lay->addWidget(p);
        }
        w->resize(350, q.size()*185);
        ui->contentScrollArea->setWidget(w);
    }
    else
        qDebug() << q.lastError().text();

}

void MainMenuDialog::on_addProductBtn_clicked()
{
    AddProductDialog* dlg = new AddProductDialog(this);
    if(dlg->exec()==QDialog::Accepted)
    {
        // save the new product in the DB
        if(!db.isOpen()) db.open();
        QSqlQuery query(db);
        query.prepare("INSERT INTO `content`"
                      "(`type`,`name`,`price`,`ingredient`,`foto`)"
                      "VALUES(:type,:name,:price,:ingredients,:foto);");

        query.bindValue(":type", dlg->ui->productTypeEdit->text());
        query.bindValue(":name", dlg->ui->productNameEdit->text());
        query.bindValue(":price", dlg->ui->productCostEdit->text());
        query.bindValue(":ingredients", dlg->ui->productContentEdit->text());
        query.bindValue(":foto", dlg->imageData);

        if(query.exec())
        {
            QMessageBox::information(this, "Продукт добавлен",
                                 "Продукт добавлен"
                                 );
            on_contentBtn_clicked();

        }
        else
            QMessageBox::warning(this, "Ошибка",
                                 "Ошибка при добавлении нового продукта:"
                                 "<br>"+query.lastError().text()
                                 );
        db.close();
    }
}

void MainMenuDialog::on_addPersonalBtn_clicked()
{
    //Password generator
    auto pwdGen = [](){
        qsrand(time(0));
        int count = qrand()%4+4;
        QString s;
        s.resize(count);
        for(int i=0;i<count;i++)
        {
            s[i] = QChar(qrand()%30+'0');
        }
        return s;
    };
    AddStaffDialog* dlg = new AddStaffDialog(this);
    if(dlg->exec()==QDialog::Accepted)
    {
        qDebug() << "on_saveStaff_clicked()";
        // save the new staff in the DB
        if(!db.isOpen()) db.open();
        QSqlQuery q(db);
        q.prepare("INSERT INTO `staff`"
                  "(`name`,`password`,`email`,`position`,`foto`)"
                  "VALUES(:name,:password,:email,:position,:foto);");
        q.bindValue(":name",dlg->ui->staffNameEdit->text());
        q.bindValue(":password",pwdGen());
        q.bindValue(":email",dlg->ui->staffEmailEdit->text());
        q.bindValue(":position",dlg->ui->staffPositionCombo->currentText());
        q.bindValue(":foto",dlg->imageData);

        if(q.exec())
        {
            QMessageBox::information(this, "Служащий добавлен",
                                 "Служащий добавлен!");
            on_personalBtn_clicked();
        }
        else
            QMessageBox::warning(this, "Ошибка",
                                 "Ошибка при добавлении нового служащего:"
                                 "<br>"+q.lastError().text()
                                 );
        db.close();
    }
}

void MainMenuDialog::on_managerOrderTable_cellClicked(int row, int column)
{
    QTableWidgetItem* item = ui->managerOrderTable->item(row, 0);
    int id = item->text().toInt();
    if(column==11)
    {
        CouriersManagementDialog dlg(db);
        connect(&dlg, &CouriersManagementDialog::courierSelected, [=](int courier_id)
        {
            if(!db.isOpen()) db.open();
            // accept the order
            QString sql = QString("UPDATE `order` SET "
                                  "`status`=%1, `staff_id`=%2 "
                                  "WHERE `id`=%3;")
                    .arg(OrderStatuses::ACCEPTED)
                    .arg(courier_id)
                    .arg(id);
            QString sql2 = QString("UPDATE `courier` SET "
                                  "`status`=1 "
                                  "WHERE `staff_id`=%2;")
                    .arg(courier_id);
            QSqlQuery q(db);
            if(q.exec(QString("SELECT * FROM `courier` WHERE `staff_id`=%1").arg(courier_id)))
                if(q.size()==0)
                    q.exec(QString("INSERT INTO courier(staff_id) VALUES(%1)").arg(courier_id));
            if(q.exec(sql) && q.exec(sql2) )
            {
                item->setBackgroundColor(OrderStatuses::getColor(OrderStatuses::ACCEPTED));
                item->setText(OrderStatuses::getText(OrderStatuses::ACCEPTED));
                QTableWidgetItem* item2 = ui->managerOrderTable->item(row, column+1);
                item2->setBackgroundColor(OrderStatuses::getColor(OrderStatuses::NOT_PROCESSED));
                item2->setText("Отклонить");
            }
            else
                QMessageBox::warning(this, "Ошибка", "Ошибка при принятии заказа<br>"+
                                 q.lastError().text());
        });
        dlg.exec();
    }
    else if(column==12)
    {
        // cancel the order
        QString sql = QString("UPDATE `order` SET "
                              "`status`=%1 WHERE `id`=%2")
                .arg(OrderStatuses::CANCELED)
                .arg(id);
        QSqlQuery q(db);
        if(!db.isOpen()) db.open();
        if(q.exec(sql))
        {
            item->setBackgroundColor(OrderStatuses::getColor(OrderStatuses::CANCELED));
            item->setText(OrderStatuses::getText(OrderStatuses::CANCELED));
            QTableWidgetItem* item2 = ui->managerOrderTable->item(row, column-1);
            item2->setBackgroundColor(OrderStatuses::getColor(OrderStatuses::NOT_PROCESSED));
            item2->setText("Принять");
        }
        else
            QMessageBox::warning(this, "Ошибка", "Ошибка при отмене заказа<br>"+
                             q.lastError().text());
    }
}

void MainMenuDialog::on_promoBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(PROMOTIONS_MANAGEMENT);
    delete ui->promoScrollArea->widget();
    if(!db.isOpen()) db.open();
    QSqlQuery q(db);
    QString sql = QString("SELECT * FROM `promotion`;");


    if(q.exec(sql))
    {
        QWidget *w = new QWidget;
        QVBoxLayout* lay = new QVBoxLayout;
        w->setLayout(lay);
        while(q.next())
        {
            Product* p = new Product;
            connect(p, &Product::editClicked, [=](int i)
            {
                if(!db.isOpen()) db.open();
                QSqlQuery q(db);
                if(q.exec(QString("SELECT * FROM `promotion` WHERE `id`=%1").arg(i)))
                {
                    if(q.first())
                    {
                        AddPromoAndGalleryDialog *dlg = new AddPromoAndGalleryDialog(this);
                        dlg->setWindowTitle("Изменить акцию");
                        dlg->ui->addBtn->setText("Сохранить");
                        dlg->ui->nameEdit->setText(q.value("name").toString());
                        dlg->ui->descEdit->setText(q.value("description").toString());
                        dlg->imageData = q.value("foto").toByteArray();

                        if(dlg->exec()==QDialog::Accepted)
                        {
                            QSqlQuery q(db);
                            q.prepare("UPDATE `promotion` SET "
                                      "`name`=:name,"
                                      "`description`=:description,"
                                      "`foto`=:foto WHERE `id`="+q.value("id").toString()+";");
                            q.bindValue(":name",dlg->ui->nameEdit->text());
                            q.bindValue(":description",dlg->ui->descEdit->text());
                            q.bindValue(":foto",dlg->imageData);

                            if(q.exec())
                            {
                                QMessageBox::information(this, "Сохранено", "Сохранено");
                                on_promoBtn_clicked();
                            }
                            else
                                QMessageBox::warning(this, "Ошибка", "Не сохранено");
                        }
                    }
                }

            });
            connect(p, &Product::delClicked, [=](int i)
            {
                QSqlQuery q(db);
                if(q.exec(QString("DELETE FROM `promotion` WHERE `id`=%1;").arg(i)))
                {
                    QMessageBox::information(this, "Акция удалена", "Акция удалена");
                } else
                    QMessageBox::warning(this, "Ошибка", "Акция не удалена");
            });
            p->setId(q.value(0).toInt());
            p->setProductName(q.value("name").toString());
            p->setProductDescription(q.value("description").toString());
            p->setProductPhoto(q.value("foto").toByteArray());
            lay->addWidget(p);
        }
        w->resize(350, q.size()*190);
        ui->promoScrollArea->setWidget(w);
    }
    else
        qDebug() << q.lastError().text();
}

void MainMenuDialog::on_galleryBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(GALLERY_MANAGEMENT);
    delete ui->galleryScrollArea->widget();
    if(!db.isOpen()) db.open();
    QSqlQuery q(db);
    QString sql = QString("SELECT * FROM `gallery`;");


    if(q.exec(sql))
    {
        QWidget *w = new QWidget;
        QVBoxLayout* lay = new QVBoxLayout;
        w->setLayout(lay);
        while(q.next())
        {
            Product* p = new Product;
            connect(p, &Product::editClicked, [=](int i)
            {
                if(!db.isOpen()) db.open();
                QSqlQuery q(db);
                if(q.exec(QString("SELECT * FROM `gallery` WHERE `id`=%1").arg(i)))
                {
                    if(q.first())
                    {
                        AddPromoAndGalleryDialog *dlg = new AddPromoAndGalleryDialog(this);
                        dlg->setWindowTitle("Изменить фото");
                        dlg->ui->addBtn->setText("Сохранить");
                        dlg->ui->nameEdit->setText(q.value("name").toString());
                        dlg->ui->descEdit->setText(q.value("description").toString());
                        dlg->imageData = q.value("foto").toByteArray();

                        if(dlg->exec()==QDialog::Accepted)
                        {
                            QSqlQuery q(db);
                            q.prepare("UPDATE `gallery` SET "
                                      "`name`=:name,"
                                      "`description`=:description,"
                                      "`foto`=:foto WHERE `id`="+QString::number(q.value("id").toInt())+";");
                            q.bindValue(":name",dlg->ui->nameEdit->text());
                            q.bindValue(":description",dlg->ui->descEdit->text());
                            q.bindValue(":foto",dlg->imageData);

                            if(q.exec())
                            {
                                QMessageBox::information(this, "Сохранено", "Сохранено");
                                on_galleryBtn_clicked();
                            }
                            else
                                QMessageBox::warning(this, "Ошибка", "Не сохранено");
                        }
                    }
                }

            });
            connect(p, &Product::delClicked, [=](int i)
            {
                QSqlQuery q(db);
                if(q.exec(QString("DELETE FROM `gallery` WHERE `id`=%1;").arg(i)))
                {
                    QMessageBox::information(this, "Фото удалено", "Фото удалено");
                } else
                QMessageBox::warning(this, "Ошибка", "Фото не удалено");
            });
            p->setId(q.value(0).toInt());
            p->setProductName(q.value("name").toString());
            p->setProductDescription(q.value("description").toString());
            p->setProductPhoto(q.value("foto").toByteArray());
            lay->addWidget(p);
        }
        w->resize(350, q.size()*190);
        ui->galleryScrollArea->setWidget(w);
    }
    else
        qDebug() << q.lastError().text();
}

void MainMenuDialog::on_addPromoBtn_clicked()
{
    AddPromoAndGalleryDialog* dlg = new AddPromoAndGalleryDialog(this);
    dlg->setWindowTitle("Добавить акцию");
    if(dlg->exec()==QDialog::Accepted)
    {
        // save the new product in the DB
        if(!db.isOpen()) db.open();
        QSqlQuery query(db);
        query.prepare("INSERT INTO `promotion`"
                      "(`name`,`description`,`foto`)"
                      "VALUES(:name,:description,:foto);");

        query.bindValue(":name", dlg->ui->nameEdit->text());
        query.bindValue(":description", dlg->ui->descEdit->text());
        query.bindValue(":foto", dlg->imageData);

        if(query.exec())
        {
            QMessageBox::information(this, "Акция добавлена",
                                 "Акция добавлена"
                                 );
            on_promoBtn_clicked();

        }
        else
            QMessageBox::warning(this, "Ошибка",
                                 "Ошибка при добавлении новой акции:"
                                 "<br>"+query.lastError().text()
                                 );
        db.close();
    }
}

void MainMenuDialog::on_addPhotoBtn_clicked()
{
    AddPromoAndGalleryDialog* dlg = new AddPromoAndGalleryDialog(this);
    dlg->setWindowTitle("Добавить фото");
    if(dlg->exec()==QDialog::Accepted)
    {
        // save the new product in the DB
        if(!db.isOpen()) db.open();
        QSqlQuery query(db);
        query.prepare("INSERT INTO `gallery`"
                      "(`name`,`description`,`foto`)"
                      "VALUES(:name,:description,:foto);");

        query.bindValue(":name", dlg->ui->nameEdit->text());
        query.bindValue(":description", dlg->ui->descEdit->text());
        query.bindValue(":foto", dlg->imageData);

        if(query.exec())
        {
            QMessageBox::information(this, "Фото добавлено",
                                 "Фото добавлено"
                                 );
            on_galleryBtn_clicked();

        }
        else
            QMessageBox::warning(this, "Ошибка",
                                 "Ошибка при добавлении нового фото:"
                                 "<br>"+query.lastError().text()
                                 );
        db.close();
    }
}
