#ifndef RECOVERYPASSWORDDIALOG_H
#define RECOVERYPASSWORDDIALOG_H

#include <QDialog>

namespace Ui {
class RecoveryPasswordDialog;
}

class RecoveryPasswordDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecoveryPasswordDialog(QWidget *parent = 0);
    ~RecoveryPasswordDialog();

    Ui::RecoveryPasswordDialog *ui;
private slots:

    void on_buttonBox_accepted();
};

#endif // RECOVERYPASSWORDDIALOG_H
