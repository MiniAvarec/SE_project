#ifndef ADDPROMOANDGALLERYDIALOG_H
#define ADDPROMOANDGALLERYDIALOG_H

#include <QDialog>
#include <QByteArray>

namespace Ui {
class AddPromoAndGalleryDialog;
}

class AddPromoAndGalleryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddPromoAndGalleryDialog(QWidget *parent = 0);
    ~AddPromoAndGalleryDialog();
    QByteArray imageData;

private slots:
    void on_photoBtn_clicked();

public:
    Ui::AddPromoAndGalleryDialog *ui;
};

#endif // ADDPROMOANDGALLERYDIALOG_H
