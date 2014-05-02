#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include "logindialog.h"
#include "ui_logindialog.h"
#include <QSqlQuery>

#define LOGIN "root"
#define PASSWD "root123"
//#define HOST "128.199.194.57"
#define HOST "188.226.183.188"
#define DBNAME "express_catering"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    staffPosition="";

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(HOST);
    db.setDatabaseName(DBNAME);
    db.setUserName(LOGIN);
    db.setPassword(PASSWD);

    ShowLoginDialog();

    ui->stackedWidget->setCurrentIndex(0);

    //QPluginLoader loader("E:/Qt/Qt5.2.0/5.2.0/mingw48_32/plugins/sqldrivers/qsqlmysqld.dll");
    //loader.load();
    //qDebug() << loader.errorString();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::ShowLoginDialog()
{
    setHidden(true);
    LoginDialog* d = new LoginDialog(this);

    connect(d->ui->pushButton, &QPushButton::clicked, [=]()
    {
        if(Authenticate(d->ui->loginEdit->text(), d->ui->passwdEdit->text()))
        {
            setHidden(false);
            d->deleteLater();
        }
    });
    connect(d, &LoginDialog::rejected, [=]()
    {
        exit(0);
    });

    d->show();

    /*while(true)
    {
        int res = d->exec();
        if(res==QDialog::Accepted)
        {
            if(Authenticate(d->ui->loginEdit->text(), d->ui->passwdEdit->text()))
            {
                setHidden(false);
                d->deleteLater();
                return;
            }
            else
                QMessageBox::warning(d, "Ошибка", "Неверная пара логин / пароль");
        }
        else if(res==QDialog::Rejected)
        {
            qDebug() << "Exit!";
            exit(0);
        }
    }*/

}

void Dialog::ShowDbError()
{
    QSqlError er=db.lastError();
    QMessageBox::warning(this, "Ошибка БД", er.text());
}

bool Dialog::ConnectToDataBase()
{

    if(db.isOpen()) return true;

    if(db.open())
        return true;
    else
    {
        QSqlError er=db.lastError();
        QMessageBox::warning(this, "Ошибка при соединении с БД", er.text());
        return false;
    }
}

void Dialog::on_pushButton_clicked()
{
    staffPosition="";
    ShowLoginDialog();
}

void Dialog::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
}

void Dialog::on_pushButton_3_clicked()
{
    if(ui->lineEdit->text()=="1")
    {
        QMessageBox::information(this, "Success", "Order has ben added successfuly");
        ui->stackedWidget->setCurrentIndex(0);
    }
    else
    {
        QMessageBox::information(this, "Fail", "Error. Order not added");
    }
}

bool Dialog::Authenticate(QString login, QString passwd)
{
    if(!ConnectToDataBase())
        return false;

    QString sql = QString("SELECT * FROM staff WHERE name='%1' AND password='%2';").arg(login).arg(passwd);

    QSqlQuery q(sql);

    db.close();

    while(q.next())
    {
        staffPosition = q.value("position").toString();
    }

    return (q.size()>0);

    //return (login=="pompon" && passwd=="123");
}
