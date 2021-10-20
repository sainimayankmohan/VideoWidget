#-------------------------------------------------
#
# Project created by QtCreator 2021-10-19T16:17:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia multimediawidgets

CONFIG += c++11

TARGET = videowidget
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    gallery.cpp \
    thumbnail.cpp \
    elements.cpp

HEADERS  += widget.h \
    gallery.h \
    thumbnail.h \
    elements.h

RESOURCES += \
    videoresource.qrc
