#include "couriersmanagementdialog.h"
#include "ui_couriersmanagementdialog.h"
#include <QMessageBox>

CouriersManagementDialog::CouriersManagementDialog(QSqlDatabase &db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CouriersManagementDialog)
{
    ui->setupUi(this);

    // retrieve list of the couriers from the DB
    // Fill the table
    if(!db.isOpen()) db.open();
    QSqlQuery q(db);
    QString sql = "SELECT `staff`.*, `courier`.status FROM `staff` LEFT JOIN `courier` ON (`courier`.staff_id = `staff`.id) WHERE (`staff`.position='Courier');";
    if(q.exec(sql))
    {
        while(q.next())
        {
            QSqlRecord rec = q.record();
            if(q.at()==0)
            {
                QStringList labels;
                labels << "ID" << "Кто" << "Состояние" << "Действие";
                ui->tableWidget->setColumnCount(4);
                ui->tableWidget->setRowCount(q.size());
                ui->tableWidget->setHorizontalHeaderLabels(labels);
                ui->tableWidget->setColumnHidden(0, true);
            }
            ui->tableWidget->setItem(q.at(), 0, new QTableWidgetItem(rec.value("id").toString()));
            ui->tableWidget->setItem(q.at(), 1, new QTableWidgetItem(rec.value("name").toString()));
            int status = rec.value("status").toInt();
            if(status==0)
            {
                ui->tableWidget->setItem(q.at(), 2, new QTableWidgetItem("Свободен"));
            }
            else
            {
                ui->tableWidget->setItem(q.at(), 2, new QTableWidgetItem("Занят"));
            }

            ui->tableWidget->setItem(q.at(), 3, new QTableWidgetItem("Назначить"));
        }
    }
    else
        QMessageBox::warning(this, "Ошибка", "Не удалось выполнить запрос: "+q.lastError().text());
}

CouriersManagementDialog::~CouriersManagementDialog()
{
    delete ui;
}

void CouriersManagementDialog::on_tableWidget_cellClicked(int row, int column)
{
    if(column==3)
    {
        emit courierSelected(ui->tableWidget->item(row, 0)->text().toInt());
        accept();
    }
}
