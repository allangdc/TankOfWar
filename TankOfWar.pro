#-------------------------------------------------
#
# Project created by QtCreator 2015-10-27T00:19:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TankOfWar
TEMPLATE = app


SOURCES += main.cpp \
    tank.cpp \
    gameviewer.cpp \
    scenegame.cpp \
    button.cpp \
    buttonleft.cpp \
    buttonright.cpp

HEADERS  += \
    tank.h \
    gameviewer.h \
    scenegame.h \
    button.h \
    buttonleft.h \
    buttonright.h

FORMS    +=

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    image.qrc

