#-------------------------------------------------
#
# Project created by QtCreator 2010-10-21T19:50:07
#
#-------------------------------------------------

QT       += core gui

TARGET = TouchTracer
TEMPLATE = app

CONFIG += link_pkgconfig
PKGCONFIG += opencv

SOURCES += main.cpp\
        mainwindow.cpp \
    imageprocessor.cpp \
    modulevideo.cpp \
    module.cpp

HEADERS  += mainwindow.h \
    module.h \
    imageprocessor.h \
    modulevideo.h

FORMS    += mainwindow.ui
