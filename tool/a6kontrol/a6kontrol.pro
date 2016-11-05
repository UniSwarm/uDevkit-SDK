QT       += core gui widgets serialport printsupport

TARGET = a6kontrol
TEMPLATE = app

DESTDIR = $$PWD/../../bin

SOURCES += main.cpp \
        mainwindow.cpp \
        protocole.cpp \
        map.cpp \
        robot.cpp \
        $$_PRO_FILE_PWD_/../../contrib/qcustomplot/qcustomplot.cpp

HEADERS += mainwindow.h \
        protocole.h \
        map.h \
        robot.h \
        $$_PRO_FILE_PWD_/../../contrib/qcustomplot/qcustomplot.h

INCLUDEPATH += $$_PRO_FILE_PWD_/../../contrib/qcustomplot/

FORMS    += mainwindow.ui
