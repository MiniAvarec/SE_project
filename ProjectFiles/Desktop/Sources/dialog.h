#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    bool Authenticate(QString login, QString passwd);
    void ShowLoginDialog();
    void ShowDbError();

private:
    Ui::Dialog *ui;
    QString staffLogin, staffPasswd, staffPosition;
    QSqlDatabase db;
    bool isAdmin() { return staffPosition=="Administrator"; }
    bool ConnectToDataBase();
};

#endif // DIALOG_H
