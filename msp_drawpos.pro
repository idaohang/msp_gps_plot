#-------------------------------------------------
#
# Project created by QtCreator 2014-06-16T00:37:51
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = msp_drawpos
TEMPLATE = app


SOURCES += main.cpp\
        startdialog.cpp \
    mspcomms.cpp \
    drawpos.cpp

HEADERS  += startdialog.h \
    mspcomms.h \
    drawpos.h

FORMS    += startdialog.ui
