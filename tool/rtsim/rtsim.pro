QT += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DESTDIR = $$PWD/../../bin
TARGET = rtsim

TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    simserver.cpp \
    simclient.cpp \
    simmodules/simmodule.cpp \
    simmodules/simmodulefactory.cpp \
    simmodules/simmoduleuart.cpp

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    simserver.h \
    simclient.h \
    simmodules/simmodule.h \
    simmodules/simmodulefactory.h \
    simmodules/simmoduleuart.h

INCLUDEPATH += ../../include ../../support
