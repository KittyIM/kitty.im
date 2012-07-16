include(../../../kittyim.pri)
include(../utils/utils.pri)
include(../3rdparty/json/json.pri)
include(../3rdparty/qtwin/qtwin.pri)

TARGET       = core
DESTDIR      = $$BIN_PATH
TEMPLATE     = lib

DEFINES     += CORE_LIBRARY

SOURCES     += profiles/profilemanager.cpp \
               profiles/profiledialog.cpp \
               plugins/manager.cpp \
               tabs/tabmanager.cpp \
               argumentparser.cpp \
               jsonsettings.cpp

HEADERS     += profiles/profilemanager.h \
               profiles/profiledialog.h \
               plugins/plugininfo.h \
               plugins/manager.h \
               plugins/iplugin.h \
               tabs/tabmanager.h \
               argumentparser.h \
               jsonsettings.h \
               core_constants.h \
               core_global.h

INCLUDEPATH += $$PWD

FORMS       += profiles/profiledialog.ui

RESOURCES   += core.qrc
