include(../../gmock.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    test.cpp \
    chat.cpp \
    uichannel.cpp

HEADERS += \
    iochannel.h \
    uichannel.h \
    chat.h

