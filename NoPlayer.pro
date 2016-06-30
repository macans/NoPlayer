#-------------------------------------------------
#
# Project created by QtCreator 2016-06-28T21:58:33
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets network script widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NoPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    musicwidget.cpp \
    menuwidget.cpp \
    controlwidget.cpp \
    playlistwidget.cpp

HEADERS  += mainwindow.h \
    musicwidget.h \
    menuwidget.h \
    controlwidget.h \
    playlistwidget.h

FORMS    +=
