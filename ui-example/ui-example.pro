#-------------------------------------------------
#
# Project created by QtCreator 2017-12-03T18:40:49
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = ui-example
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    connectionbackground.cpp \
    phnmessage.cpp \
    phnsysconfig.cpp \
    phnevent.cpp \
    phnsoundplayer.cpp

HEADERS  += mainwindow.h \
    connectionbackground.h \
    phnmessage.h \
    phnsysconfig.h \
    phnevent.h \
    phnsoundplayer.h

FORMS    += mainwindow.ui

RESOURCES += \
    icons.qrc


win32:RC_ICONS = app_100.ico

DISTFILES +=
