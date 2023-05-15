QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CProtocol.cpp \
    main.cpp \
    mainwindow.cpp \
    packethandler.cpp \
    protoFields/arp.cpp \
    protoFields/cfields.cpp \
    protoFields/chttp.cpp \
    protoFields/etherfields.cpp \
    protoFields/icmp.cpp \
    protoFields/ipv4fields.cpp \
    protoFields/ipv6fields.cpp \
    protoFields/tcp.cpp \
    protoFields/udp.cpp \
    savefiledialog.cpp

HEADERS += \
    CProtocol.h \
    mainwindow.h \
    packethandler.h \
    protoFields/arp.h \
    protoFields/cfields.h \
    protoFields/chttp.h \
    protoFields/etherfields.h \
    protoFields/icmp.h \
    protoFields/ipv4fields.h \
    protoFields/ipv6fields.h \
    protoFields/tcp.h \
    protoFields/udp.h \
    savefiledialog.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    PacketCrafter_uk_UA.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#INCLUDEPATH += /usr/include/python3.8
#LIBS += -L/usr/lib/python3.8/config-3.8-x86_64-linux-gnu
#LIBS += -L/usr/lib -lpython3.8 -lcrypt -lpthread -ldl  -lutil -lm -lm
