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
    tankcontrolbutton.cpp \
    tankcontrolleft.cpp \
    tankcontrolright.cpp \
    tankcontrolforward.cpp \
    bomb.cpp \
    tankcontrolfire.cpp \
    progressbar.cpp

HEADERS  += \
    tank.h \
    gameviewer.h \
    scenegame.h \
    tankcontrolbutton.h \
    tankcontrolleft.h \
    tankcontrolright.h \
    tankcontrolforward.h \
    bomb.h \
    tankcontrolfire.h \
    progressbar.h

FORMS    +=

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    image.qrc

