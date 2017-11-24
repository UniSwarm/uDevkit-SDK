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
    simmodules/simmodule_uart.cpp \
    simmodules/simmodule_adc.cpp \
    simmodules/simmodule_mrobot.cpp \
    widgets/guiwidget/screenwidget.cpp \
    widgets/uartwidget/uartwidget.cpp \
    widgets/adcwidget/adcwidget.cpp \
    widgets/guiwidget/guiwidget.cpp \
    simproject.cpp

FORMS +=

HEADERS += \
    mainwindow.h \
    simserver.h \
    simclient.h \
    simmodules/simmodule.h \
    simmodules/simmodulefactory.h \
    simmodules/simmodule_gui.h \
    simmodules/simmodule_uart.h \
    simmodules/simmodule_adc.h \
    simmodules/simmodule_mrobot.h \
    widgets/guiwidget/screenwidget.h \
    widgets/uartwidget/uartwidget.h \
    widgets/adcwidget/adcwidget.h \
    widgets/guiwidget/guiwidget.h \
    simproject.h

INCLUDEPATH += ../../include ../../support
