TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.cpp \
    server.cpp \
    open62541.c \
    opcuavariable.cpp

HEADERS += \
    open62541.h \
    server.h
