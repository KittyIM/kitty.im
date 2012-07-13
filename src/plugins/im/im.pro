include(../../../kittyim.pri)
include(../../libs/core/core.pri)

TARGET   = im
DESTDIR  = $$PLUGIN_PATH
TEMPLATE = lib

DEFINES += IM_LIBRARY

SOURCES += \
    plugin.cpp

HEADERS += \
           im_global.h \
    plugin.h
