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
    playlistwidget.cpp \
    videowidget.cpp \
    playcontrols.cpp \
    about_ui.cpp \
    subtitlelabel.cpp \
    searchwindow.cpp \
    controlwindow.cpp \
    shortcut.cpp


HEADERS  += mainwindow.h \
    musicwidget.h \
    menuwidget.h \
    playlistwidget.h \
    videowidget.h \
    playcontrols.h \
    about_ui.h \
    subtitlelabel.h \
    playconfig.h \
    searchwindow.h \
    controlwindow.h \
    shortcut.h



FORMS    += controlwindow.ui \
    about_ui.ui \
    shortcut.ui


RESOURCES += \
    images.qrc
