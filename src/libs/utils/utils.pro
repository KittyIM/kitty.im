include(../../../kittyim.pri)

QT          -= gui

TARGET       = utils
DESTDIR      = $$BIN_PATH
TEMPLATE     = lib

DEFINES     += UTILS_LIBRARY

SOURCES     += utils.cpp

HEADERS     += utils.h \
               utils_global.h

INCLUDEPATH += $$PWD
