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
    playlistwindow.cpp \
    videowidget.cpp \
    playcontrols.cpp \
    subtitlelabel.cpp \
    searchwindow.cpp \
    controlwindow.cpp \
    shortcut.cpp \
    propertywidget.cpp \
    aboutwidget.cpp

HEADERS  += mainwindow.h \
    musicwidget.h \
    playlistwindow.h \
    videowidget.h \
    playcontrols.h \
    subtitlelabel.h \
    playconfig.h \
    searchwindow.h \
    controlwindow.h \
    shortcut.h \
    propertywidget.h \
    aboutwidget.h



FORMS    += controlwindow.ui \
    shortcut.ui

RESOURCES += \
    images.qrc

