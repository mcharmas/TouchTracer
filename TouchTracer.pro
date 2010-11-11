#-------------------------------------------------
#
# Project created by QtCreator 2010-10-21T19:50:07
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = TouchTracer
TEMPLATE = app

CONFIG += link_pkgconfig
PKGCONFIG += opencv

include(Modules/Modules.pri)
include(TUIO/TUIO.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    modulemanagerwidget.cpp \
    videogallery.cpp

HEADERS  += mainwindow.h \
    modulemanagerwidget.h \
    videogallery.h

FORMS    += mainwindow.ui \
    modulemanagerwidget.ui

