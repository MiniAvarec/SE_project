#include "staff.h"
#include "ui_staff.h"

Staff::Staff(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Staff)
{
    ui->setupUi(this);
    ui->editBtn->setHidden(true);
    ui->delBtn->setHidden(true);
}

Staff::~Staff()
{
    delete ui;
}

void Staff::setForAdmin()
{
    ui->editBtn->setHidden(false);
    ui->delBtn->setHidden(false);
}

void Staff::setPhoto(const QByteArray photoData)
{
    QPixmap p = QPixmap();
    p.loadFromData(photoData);
    ui->photoLabel->setPixmap(p);
}

void Staff::on_editBtn_clicked()
{
    emit editClicked(id);
}

void Staff::on_delBtn_clicked()
{
    emit delClicked(id);
}
