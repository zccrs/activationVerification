#-------------------------------------------------
#
# Project created by QtCreator 2015-07-16T09:16:50
#
#-------------------------------------------------

QT       += core gui dbus

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = activationVerification
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    inputdialog.cpp

HEADERS  += mainwindow.h \
    inputdialog.h

include(Qt AES_ECB/aes.pri)

TRANSLATIONS += i18n/activationVerification_zh.ts

RESOURCES += \
    ts.qrc


target.path = /usr/bin/
INSTALLS += target
