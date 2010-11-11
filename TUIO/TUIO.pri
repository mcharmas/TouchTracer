HEADERS += TUIO/TuioContainer.h \
	   TUIO/TuioCursor.h \
	   TUIO/TuioObject.h \
	   TUIO/TuioPoint.h \ 
           TUIO/TuioServer.h \
	   TUIO/TuioTime.h

SOURCES += TUIO/TuioServer.cpp \
           TUIO/TuioTime.cpp

include(osc/osc.pri)
include(ip/ip.pri)