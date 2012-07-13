include(../../../kittyim.pri)
include(../../libs/pluginsystem/pluginsystem.pri)

TARGET   = coreplugin
DESTDIR  = $$PLUGIN_PATH
TEMPLATE = lib

DEFINES += COREPLUGIN_LIBRARY

SOURCES += coreplugin.cpp

HEADERS += coreplugin.h\
           coreplugin_global.h
