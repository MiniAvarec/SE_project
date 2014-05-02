#include "product.h"
#include "ui_product.h"
#include <QPixmap>

Product::Product(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Product)
{
    ui->setupUi(this);
}

Product::~Product()
{
    delete ui;
}

void Product::setProductName(const QString& n)
{
    ui->nameLabel->setText(n);
}

void Product::setProductDescription(const QString &d)
{
    ui->descLabel->setText(d);
}

void Product::setProductPhoto(const QByteArray &a)
{
    QPixmap p = QPixmap();
    p.loadFromData(a);
    ui->photoLabel->setPixmap(p);
}

QString Product::getProductName() const
{
    ui->nameLabel->text();
}

QString Product::getProductDescription() const
{
    ui->descLabel->text();
}

void Product::on_editBtn_clicked()
{
    emit editClicked(id);
}

void Product::on_delBtn_clicked()
{
    emit delClicked(id);
}
