#-------------------------------------------------
#
# Project created by QtCreator 2015-10-28T12:02:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mouse_isoni
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH +=  D:\\choosecv\\include \
                D:\\choosecv\\include\\opencv \
                D:\\choosecv\\include\\opencv2 \

LIBS +=  D:\\choosecv\\lib\\opencv_world300.lib \
         D:\\choosecv\\lib\\opencv_ts300.lib \
         D:\\choosecv\\lib\\opencv_world300d.lib \
         D:\\choosecv\\lib\\opencv_ts300d.lib
