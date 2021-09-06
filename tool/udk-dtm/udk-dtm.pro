QT -= gui
QT += xml concurrent

CONFIG += c++11 console
CONFIG -= app_bundle
QMAKE_CXXFLAGS_RELEASE -= -O1 -O2
QMAKE_CXXFLAGS_RELEASE *= -Os

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        cwritter.cpp \
        edcdb.cpp \
        edcparser.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    cwritter.h \
    edcdb.h \
    edcparser.h
