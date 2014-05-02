#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

    Ui::LoginDialog *ui;
private slots:

    void on_forgotBtn_clicked();
};

#endif // LOGINDIALOG_H
