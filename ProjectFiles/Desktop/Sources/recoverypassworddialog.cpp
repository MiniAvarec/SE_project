#include "recoverypassworddialog.h"
#include "ui_recoverypassworddialog.h"
#include <QDebug>
#include "QtNetwork/qnetworkaccessmanager.h"
#include <QtNetwork/QtNetwork>

RecoveryPasswordDialog::RecoveryPasswordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecoveryPasswordDialog)
{
    ui->setupUi(this);
}

RecoveryPasswordDialog::~RecoveryPasswordDialog()
{
    delete ui;
}



void RecoveryPasswordDialog::on_buttonBox_accepted()
{
    qDebug() << "works";
    QString email = ui->lineEdit->text();
    qDebug() << email;
    QNetworkAccessManager * pManager = new QNetworkAccessManager;
    connect(pManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinish(QNetworkReply*)));
    QString urlka = "http://miniavarec.tk/forgotpass.php?mail="+email;
    qDebug() << urlka;
    pManager->get(QNetworkRequest(QUrl(urlka)));
}
