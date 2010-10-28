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
    module.cpp \
    modulemanagerwidget.cpp \
    videogallery.cpp \
    abstractsettingswidget.cpp

HEADERS  += mainwindow.h \
    module.h \
    imageprocessor.h \
    modulevideo.h \
    modulemanagerwidget.h \
    videogallery.h \
    abstractsettingswidget.h

FORMS    += mainwindow.ui \
    modulemanagerwidget.ui \
    abstractsettingswidget.ui
