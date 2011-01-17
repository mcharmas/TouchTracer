QT       += core gui opengl

TARGET = TouchTracer
TEMPLATE = app

include(Modules/Modules.pri)
include(TUIO/TUIO.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    modulemanagerwidget.cpp \
    videogallery.cpp \
    cameraselectiondialog.cpp

HEADERS  += mainwindow.h \
    modulemanagerwidget.h \
    videogallery.h \
    cameraselectiondialog.h

FORMS    += mainwindow.ui \
    modulemanagerwidget.ui \
    cameraselectiondialog.ui

win32:INCLUDEPATH += C:\OpenCV-2.1.0\include\opencv
win32:LIBS += -L"C:\OpenCV-2.1.0\out\bin" \
        -lcxcore210 \
        -lcv210 \
        -lcvaux210 \
        -lhighgui210 \
        -lml210 \
        -lws2_32 \
        -lwinmm

unix:CONFIG += link_pkgconfig
unix:PKGCONFIG += opencv