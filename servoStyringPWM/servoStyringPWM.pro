TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    server.cpp

INCLUDEPATH += C:\Users\vikpo\Desktop\Libaries\wiringPi
INCLUDEPATH += C:\Users\vikpo\Desktop\Libaries\open62541-win64\build

HEADERS += \
    server.h
