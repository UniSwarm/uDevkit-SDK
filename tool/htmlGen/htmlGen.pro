QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DESTDIR = $$PWD/../../bin

TARGET = htmlGen

TEMPLATE = app

SOURCES += htmlGen.cpp
