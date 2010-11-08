

HEADERS += Modules/abstractsettingswidget.h \
    Modules/imageprocessor.h \
    Modules/module.h \
    Modules/videowidget.h \
    Modules/glvideo.h

SOURCES += Modules/abstractsettingswidget.cpp \
   Modules/imageprocessor.cpp  \
   Modules/module.cpp \
   Modules/videowidget.cpp \
    Modules/glvideo.cpp

FORMS += Modules/abstractsettingswidget.ui \
        Modules/videowidget.ui

include(ModuleVideo.pri)
include(ModuleBackground.pri)
include(ModuleFilters.pri)
include(ModuleTracking.pri)
