QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DESTDIR = $$PWD/../../bin

TARGET = img2raw

TEMPLATE = app

SOURCES += img2raw.cpp
