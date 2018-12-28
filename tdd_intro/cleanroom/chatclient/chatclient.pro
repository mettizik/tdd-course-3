!unix:include(../../gmock.pri)
unix:LIBS += -lgmock -lgtest -lpthread
win32:LIBS += -lws2_32

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    test.cpp \
    chat.cpp \
    uichannel.cpp \
    __socket.cpp \
    socket_tests.cpp \
    socketchannel.cpp \
    fabric.cpp \
    server.cpp \
    client.cpp \
    main.cpp

HEADERS += \
    iochannel.h \
    uichannel.h \
    chat.h \
    __socket.h \
    socketchannel.h \
    fabric.h \
    chatparticipant.h \
    server.h \
    client.h

