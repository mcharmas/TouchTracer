HEADERS += TUIO/ip/IpEndpointName.h \
           TUIO/ip/NetworkingUtils.h \
	   TUIO/ip/PacketListener.h \
           TUIO/ip/TimerListener.h \
	   TUIO/ip/UdpSocket.h

SOURCES += TUIO/ip/IpEndpointName.cpp

win32 {
SOURCES += TUIO/ip/win32/NetworkingUtils.cpp \
           TUIO/ip/win32/UdpSocket.cpp
}

unix {
SOURCES += TUIO/ip/posix/NetworkingUtils.cpp \
           TUIO/ip/posix/UdpSocket.cpp
}
