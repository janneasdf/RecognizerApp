#-------------------------------------------------
#
# Project created by QtCreator 2016-05-13T15:33:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RecognizerApp
TEMPLATE = app

CONFIG += qt debug

INCLUDEPATH += BallCommunication/Libraries/

contains(QT_ARCH, i386) {
    LIBS += "-LE:/Research/Sensorball/New stuff/RecognizerApp/BallCommunication/Libraries/SDL/x86/lib" -lSDL
    LIBS += "-LE:/Research/Sensorball/New stuff/RecognizerApp/BallCommunication/Libraries/SDL/x86/lib" -lSDL_net
} else {
    LIBS += "-LE:/Research/Sensorball/New stuff/RecognizerApp/BallCommunication/Libraries/SDL/x64/lib" -lSDL
    LIBS += "-LE:/Research/Sensorball/New stuff/RecognizerApp/BallCommunication/Libraries/SDL/x64/lib" -lSDL_net
}

SOURCES += main.cpp\
        mainwindow.cpp \
    BallCommunication/Networking/BallCommunicator/BallCommunicator.cpp \
    BallCommunication/Networking/BallCommunicator/BallCommunicator_UDP.cpp \
    BallCommunication/Networking/Network/Network.cpp \
    BallCommunication/Networking/Network/UDPClientSession.cpp \
    BallCommunication/Networking/Network/UDPServerSession.cpp \
    BallCommunication/Networking/RS232C/rs232c.cpp \
    BallCommunication/Networking/Timer/Timer.cpp \
    BallCommunication/Utilities/AccelerometerCalibrator/AccelerometerCalibrator.cpp \
    BallCommunication/Utilities/GyroCalibrator/GyroCalibrator.cpp \
    BallCommunication/ballcommunication.cpp \
    GestureRecognition/gesturerecognition.cpp \
    mainlogic.cpp \
    monitor.cpp \
    monitorview.cpp

HEADERS  += mainwindow.h \
    BallCommunication/Networking/BallCommunicator/BallCommunicator.h \
    BallCommunication/Networking/BallCommunicator/BallCommunicator_UDP.h \
    BallCommunication/Networking/Network/Network.h \
    BallCommunication/Networking/Network/UDPClientSession.h \
    BallCommunication/Networking/Network/UDPServerSession.h \
    BallCommunication/Networking/RS232C/rs232c.h \
    BallCommunication/Networking/Timer/Timer.h \
    BallCommunication/Utilities/AccelerometerCalibrator/AccelerometerCalibrator.h \
    BallCommunication/Utilities/GyroCalibrator/GyroCalibrator.h \
    BallCommunication/ballcommunication.h \
    BallCommunication/declaration.h \
    GestureRecognition/gesturerecognition.h \
    mainlogic.h \
    monitor.h \
    monitorview.h

FORMS    += mainwindow.ui
