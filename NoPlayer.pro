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
    playlistmodel.cpp \
    videowidget.cpp \
    playcontrols.cpp \
    about_ui.cpp


HEADERS  += mainwindow.h \
    musicwidget.h \
    menuwidget.h \
    controlwidget.h \
    playlistmodel.h \
    videowidget.h \
    playcontrols.h \
    about_ui.h


FORMS    += mainwindow.ui \
    controlwidget.ui \
    about_ui.ui
