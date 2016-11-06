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
    simmodules/simmodule_gui.cpp \
    widgets/screenwidget.cpp \
    simmodules/simmodule_uart.cpp

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    simserver.h \
    simclient.h \
    simmodules/simmodule.h \
    simmodules/simmodulefactory.h \
    simmodules/simmodule_gui.h \
    widgets/screenwidget.h \
    simmodules/simmodule_uart.h

INCLUDEPATH += ../../include ../../support
