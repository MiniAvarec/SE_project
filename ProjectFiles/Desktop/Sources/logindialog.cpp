#include "logindialog.h"
#include "ui_logindialog.h"
#include <QPushButton>
#include "recoverypassworddialog.h"
#include "ui_recoverypassworddialog.h"
#include <QDebug>
#include "QtNetwork/qnetworkaccessmanager.h"
#include <QtNetwork/QtNetwork>
#include <QProcess>


LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    QProcess *process = new QProcess(this);
    QString program = "explorer.exe";
    QString folder = "C:\\Windows\\System32\\osk.exe";
    process->start(program, QStringList() << folder);


}

LoginDialog::~LoginDialog()
{
    delete ui;
}

// Recovery password
void LoginDialog::on_forgotBtn_clicked()
{
    /*setHidden(true);
    RecoveryPasswordDialog dlg(this);
    if(dlg.exec()==QDialog::Accepted)
    {
        QString email = dlg.ui->lineEdit->text();
        qDebug() << email;
        //Request to server
    }
    setHidden(false);*/}
