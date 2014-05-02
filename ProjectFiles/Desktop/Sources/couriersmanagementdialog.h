#ifndef COURIERSMANAGEMENTDIALOG_H
#define COURIERSMANAGEMENTDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

namespace Ui {
class CouriersManagementDialog;
}

class CouriersManagementDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CouriersManagementDialog(QSqlDatabase& db, QWidget *parent = 0);
    ~CouriersManagementDialog();

private slots:
    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::CouriersManagementDialog *ui;

signals:
    void courierSelected(int);
};

#endif // COURIERSMANAGEMENTDIALOG_H
