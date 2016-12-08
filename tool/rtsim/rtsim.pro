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
    widgets/guiwidget/screenwidget.cpp \
    simmodules/simmodule_uart.cpp \
    simmodules/simmodule_mrobot.cpp \
    widgets/uartwidget/uartwidget.cpp \
    widgets/guiwidget/guiwidget.cpp

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    simserver.h \
    simclient.h \
    simmodules/simmodule.h \
    simmodules/simmodulefactory.h \
    simmodules/simmodule_gui.h \
    widgets/guiwidget/screenwidget.h \
    simmodules/simmodule_uart.h \
    simmodules/simmodule_mrobot.h \
    widgets/uartwidget/uartwidget.h \
    widgets/guiwidget/guiwidget.h

INCLUDEPATH += ../../include ../../support
