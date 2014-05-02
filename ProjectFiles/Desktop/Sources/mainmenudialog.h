#ifndef MAINMENUDIALOG_H
#define MAINMENUDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include "mainobject.h"

namespace Ui {
class MainMenuDialog;
}

class MainMenuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenuDialog(QWidget *parent = 0);
    ~MainMenuDialog();
    void init(const QSqlDatabase &_db, const RegistrationData& _rd)
    {
        if(_rd.staffPosition=="Administrator") isAdmin=true;
        else isAdmin=false;
        db=_db;
    }
    enum Windows{MAIN_MENU=0,
                 MANAGER_ORDERS_MANAGEMENT,
                 CONTENT_MANAGEMENT,
                 DELIVERY_VIEW,
                 ADMIN_STAFF,
                 ADMIN_ORDERS_VIEW,
                 MANAGER_STAFF,
                 PROMOTIONS_MANAGEMENT,
                 GALLERY_MANAGEMENT
                };

private slots:
    void on_ordersBtn_clicked();
    void backButton_clicked();

    void on_deliveryBtn_clicked();

    void on_personalBtn_clicked();

    void on_contentBtn_clicked();

    void on_addProductBtn_clicked();

    void on_addPersonalBtn_clicked();

    void on_managerOrderTable_cellClicked(int row, int column);

    void on_promoBtn_clicked();

    void on_galleryBtn_clicked();

    void on_addPromoBtn_clicked();

    void on_addPhotoBtn_clicked();

private:
    Ui::MainMenuDialog *ui;
    QPushButton* backButton;
    bool isAdmin;
    QSqlDatabase db;

    class OrderStatuses{
    public:
        enum {NOT_PROCESSED=1, ACCEPTED, CANCELED};
        static QString getText(int s)
        {
            switch(s)
            {
                case NOT_PROCESSED: return "Не обработан";
                case ACCEPTED: return "Принят";
                case CANCELED: return "Отменен";
            }
        }
        static QColor getColor(int s)
        {
            switch(s)
            {
                case NOT_PROCESSED: return QColor(255,255,255);
                case ACCEPTED: return QColor(0,255,0);
                case CANCELED: return QColor(255,0,0);
            }
        }
    };
};

#endif // MAINMENUDIALOG_H
