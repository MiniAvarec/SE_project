#include "mainobject.h"
#include "logindialog.h"
#include "ui_logindialog.h"
#include "recoverypassworddialog.h"
#include "ui_recoverypassworddialog.h"
#include "mainmenudialog.h"
#include "ui_mainmenudialog.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QProcess>
#define LOGIN "root"
#define PASSWD "root123"
//#define HOST "128.199.194.57"
#define HOST "188.226.183.188"

#define DBNAME "express_catering"

MainObject::MainObject(QObject *parent) :
    QObject(parent)
{
    RegData.staffPosition="";

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(HOST);
    db.setDatabaseName(DBNAME);
    db.setUserName(LOGIN);
    db.setPassword(PASSWD);

    ShowLoginDialog();
}

void MainObject::ShowLoginDialog()
{
    LoginDialog *dlg = new LoginDialog;
    connect(dlg->ui->pushButton, &QPushButton::clicked, [=](){
        if(!ConnectToDataBase())
            return;
        if(Authenticate(dlg->ui->loginEdit->text(), dlg->ui->passwdEdit->text()))
        {
            dlg->deleteLater();
            ShowMainMenuDialog();
            QProcess p;
            p.start("taskkill /IM osk.exe");
            p.waitForFinished();
        }
        else
            QMessageBox::warning(dlg, "Ошибка аутентификации", "Неправильная пара логин / пароль");
    });
    connect(dlg->ui->forgotBtn, &QPushButton::clicked, [=](){
        dlg->deleteLater();
        ShowRecoveryPasswordDialog();
    });
    dlg->show();
}

void MainObject::ShowMainMenuDialog()
{
    MainMenuDialog* md = new MainMenuDialog;
    md->init(db, RegData);
    connect(md, &MainMenuDialog::rejected, [=]()
    {
        ShowLoginDialog();
        md->deleteLater();
    });
    md->show();
}

void MainObject::ShowRecoveryPasswordDialog()
{
    RecoveryPasswordDialog* rd = new RecoveryPasswordDialog;
    connect(rd, &RecoveryPasswordDialog::finished, [=]()
    {
        QString email = rd->ui->lineEdit->text();
        if(!email.isEmpty())
        {
            // request to server
        }
        ShowLoginDialog();
        rd->deleteLater();
    });
    rd->show();
}

bool MainObject::Authenticate(QString login, QString passwd)
{

    QString sql = QString("SELECT * FROM staff WHERE name='%1' AND password='%2';").arg(login).arg(passwd);

    QSqlQuery q(sql);

    db.close();

    while(q.next())
    {
        RegData.staffPosition = q.value("position").toString();
    }

    return (q.size()>0);
}

bool MainObject::ConnectToDataBase()
{

    if(db.isOpen()) return true;

    if(db.open())
        return true;
    else
    {
        QSqlError er=db.lastError();
        QMessageBox::warning(0, "Ошибка при соединении с БД", er.text());
        return false;
    }
}
