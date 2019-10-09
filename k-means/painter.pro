#-------------------------------------------------
#
# Project created by QtCreator 2015-09-20T22:42:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = painter
TEMPLATE = app


SOURCES += main.cpp\
        k_means.cpp \
        plot.cpp \
        widget.cpp

HEADERS  += widget.h \
    k_means.h \
    plot.h

FORMS    += widget.ui
