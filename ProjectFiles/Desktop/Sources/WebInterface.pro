#-------------------------------------------------
#
# Project created by QtCreator 2014-04-06T23:02:34
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WebInterface
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    logindialog.cpp \
    recoverypassworddialog.cpp \
    mainobject.cpp \
    mainmenudialog.cpp \
    couriersmanagementdialog.cpp \
    staff.cpp \
    product.cpp \
    addproductdialog.cpp \
    addstaffdialog.cpp \
    addpromoandgallerydialog.cpp

HEADERS  += dialog.h \
    logindialog.h \
    recoverypassworddialog.h \
    mainobject.h \
    mainmenudialog.h \
    couriersmanagementdialog.h \
    staff.h \
    product.h \
    addproductdialog.h \
    addstaffdialog.h \
    addpromoandgallerydialog.h

FORMS    += dialog.ui \
    logindialog.ui \
    recoverypassworddialog.ui \
    mainmenudialog.ui \
    couriersmanagementdialog.ui \
    staff.ui \
    product.ui \
    addproductdialog.ui \
    addstaffdialog.ui \
    addpromoandgallerydialog.ui

CONFIG += c++11

#INCLUDEPATH += "C:\Program Files\MySQL\Connector C++ 1.1.3\include"
#INCLUDEPATH += "E:\Qt\Qt5.2.0\5.2.0\mingw48_32\include\QtSql\5.2.0\QtSql\private"
#LIBS += "E:\Qt\Qt5.2.0\5.2.0\mingw48_32\plugins\sqldrivers\qsqlmysqld.dll"
#LIBS += "C:/Program Files/MySQL/MySQL Server 5.6/lib/libmysql.dll"
#QTPLUGIN += QSQLMYSQL
