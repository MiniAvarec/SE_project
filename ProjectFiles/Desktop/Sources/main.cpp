#include "mainobject.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainObject m;

    return a.exec();
}
