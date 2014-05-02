#ifndef ADDPRODUCTDIALOG_H
#define ADDPRODUCTDIALOG_H

#include <QDialog>
#include <qprocess.h>
#include <QProcess>
namespace Ui {
class AddProductDialog;
}

class AddProductDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddProductDialog(QWidget *parent = 0);
    ~AddProductDialog();

    Ui::AddProductDialog *ui;
    int id;
    QByteArray imageData;

private slots:
    void on_photoBtn_clicked();

};

#endif // ADDPRODUCTDIALOG_H
