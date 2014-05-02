#ifndef PRODUCT_H
#define PRODUCT_H

#include <QWidget>

namespace Ui {
class Product;
}

class Product : public QWidget
{
    Q_OBJECT

public:
    explicit Product(QWidget *parent = 0);
    ~Product();
    void setId(int _id) {id=_id;}
    void setProductName(const QString& n);
    void setProductDescription(const QString& d);
    void setProductPhoto(const QByteArray &a);
    QString getProductName() const;
    QString getProductDescription() const;
private:
    Ui::Product *ui;
    int id;
signals:
    void editClicked(int);
    void delClicked(int);
private slots:
    void on_editBtn_clicked();
    void on_delBtn_clicked();
};

#endif // PRODUCT_H
