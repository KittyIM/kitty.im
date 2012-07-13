include(../../../kittyim.pri)

QT       -= gui

TARGET    = pluginsystem
DESTDIR   = $$BIN_PATH
TEMPLATE  = lib

DEFINES  += PLUGINSYSTEM_LIBRARY

SOURCES  += \
    manager.cpp

HEADERS  += \
            pluginsystem_global.h \
    manager.h \
    iplugin.h

