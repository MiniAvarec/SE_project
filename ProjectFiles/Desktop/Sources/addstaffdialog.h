#ifndef ADDSTAFFDIALOG_H
#define ADDSTAFFDIALOG_H

#include <QDialog>

namespace Ui {
class AddStaffDialog;
}

class AddStaffDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddStaffDialog(QWidget *parent = 0);
    ~AddStaffDialog();
    int id;

    Ui::AddStaffDialog *ui;
    QByteArray imageData;
private slots:
    void on_photoBtn_clicked();
};

#endif // ADDSTAFFDIALOG_H
