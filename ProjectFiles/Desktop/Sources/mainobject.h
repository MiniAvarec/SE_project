#ifndef MAINOBJECT_H
#define MAINOBJECT_H

#include <QObject>
#include <QSqlDatabase>

struct RegistrationData{
    QString staffLogin, staffPasswd, staffPosition;
};

class MainObject : public QObject
{
    Q_OBJECT
public:
    explicit MainObject(QObject *parent = 0);

signals:

public slots:
    void ShowLoginDialog();
    void ShowMainMenuDialog();
    void ShowRecoveryPasswordDialog();

private:
    bool Authenticate(QString login, QString passwd);
    RegistrationData RegData;
    QSqlDatabase db;
    bool isAdmin() { return RegData.staffPosition=="Administrator"; }
    bool ConnectToDataBase();
};

#endif // MAINOBJECT_H
