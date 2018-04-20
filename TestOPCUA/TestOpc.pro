TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    open62541.c

INCLUDEPATH += C:\Users\vikpo\Desktop\Libaries\open62541-win64\build

HEADERS += \
    open62541.h
