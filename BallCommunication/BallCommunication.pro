#-------------------------------------------------
#
# Project created by QtCreator 2016-05-11T18:43:56
#
#-------------------------------------------------

QT       += core

TARGET = BallCommunication
TEMPLATE = lib
CONFIG += staticlib

SOURCES += ballcommunication.cpp \
    Networking/Network/Network.cpp \
    Networking/Network/UDPClientSession.cpp \
    Networking/Network/UDPServerSession.cpp \
    Networking/RS232C/rs232c.cpp \
    Networking/BallCommunicator/BallCommunicator.cpp \
    Networking/BallCommunicator/BallCommunicator_UDP.cpp \
    Networking/Timer/Timer.cpp \
    Utilities/AccelerometerCalibrator/AccelerometerCalibrator.cpp \
    Utilities/GyroCalibrator/GyroCalibrator.cpp

HEADERS += ballcommunication.h \
    Networking/Network/Network.h \
    Networking/Network/UDPClientSession.h \
    Networking/Network/UDPServerSession.h \
    Networking/RS232C/rs232c.h \
    Networking/BallCommunicator/BallCommunicator.h \
    Networking/BallCommunicator/BallCommunicator_UDP.h \
    Libraries/SDL/include/begin_code.h \
    Libraries/SDL/include/close_code.h \
    Libraries/SDL/include/SDL.h \
    Libraries/SDL/include/SDL_active.h \
    Libraries/SDL/include/SDL_audio.h \
    Libraries/SDL/include/SDL_byteorder.h \
    Libraries/SDL/include/SDL_cdrom.h \
    Libraries/SDL/include/SDL_config.h \
    Libraries/SDL/include/SDL_config_dreamcast.h \
    Libraries/SDL/include/SDL_config_macos.h \
    Libraries/SDL/include/SDL_config_macosx.h \
    Libraries/SDL/include/SDL_config_minimal.h \
    Libraries/SDL/include/SDL_config_nds.h \
    Libraries/SDL/include/SDL_config_os2.h \
    Libraries/SDL/include/SDL_config_symbian.h \
    Libraries/SDL/include/SDL_config_win32.h \
    Libraries/SDL/include/SDL_copying.h \
    Libraries/SDL/include/SDL_cpuinfo.h \
    Libraries/SDL/include/SDL_endian.h \
    Libraries/SDL/include/SDL_error.h \
    Libraries/SDL/include/SDL_events.h \
    Libraries/SDL/include/SDL_getenv.h \
    Libraries/SDL/include/SDL_image.h \
    Libraries/SDL/include/SDL_joystick.h \
    Libraries/SDL/include/SDL_keyboard.h \
    Libraries/SDL/include/SDL_keysym.h \
    Libraries/SDL/include/SDL_loadso.h \
    Libraries/SDL/include/SDL_main.h \
    Libraries/SDL/include/SDL_mixer.h \
    Libraries/SDL/include/SDL_mouse.h \
    Libraries/SDL/include/SDL_mutex.h \
    Libraries/SDL/include/SDL_name.h \
    Libraries/SDL/include/SDL_net.h \
    Libraries/SDL/include/SDL_opengl.h \
    Libraries/SDL/include/SDL_platform.h \
    Libraries/SDL/include/SDL_quit.h \
    Libraries/SDL/include/SDL_rwops.h \
    Libraries/SDL/include/SDL_stdinc.h \
    Libraries/SDL/include/SDL_syswm.h \
    Libraries/SDL/include/SDL_thread.h \
    Libraries/SDL/include/SDL_timer.h \
    Libraries/SDL/include/SDL_ttf.h \
    Libraries/SDL/include/SDL_types.h \
    Libraries/SDL/include/SDL_version.h \
    Libraries/SDL/include/SDL_video.h \
    Networking/Timer/Timer.h \
    Utilities/AccelerometerCalibrator/AccelerometerCalibrator.h \
    Utilities/GyroCalibrator/GyroCalibrator.h \
    declaration.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
