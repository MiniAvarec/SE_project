#ifndef STAFF_H
#define STAFF_H

#include <QWidget>

namespace Ui {
class Staff;
}

class Staff : public QWidget
{
    Q_OBJECT

public:
    explicit Staff(QWidget *parent = 0);
    ~Staff();

    Ui::Staff *ui;

    void setForAdmin();
    int id;
    void setPhoto(const QByteArray photoData);

signals:
    void editClicked(int);
    void delClicked(int);
private slots:
    void on_editBtn_clicked();
    void on_delBtn_clicked();
};

#endif // STAFF_H
