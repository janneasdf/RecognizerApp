#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T19:39:39
#
#-------------------------------------------------

QT       += core

TARGET = GestureRecognition
TEMPLATE = lib
CONFIG += staticlib

SOURCES += gesturerecognition.cpp

HEADERS += gesturerecognition.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
