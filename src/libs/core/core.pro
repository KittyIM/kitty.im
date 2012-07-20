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
               plugins/pluginmanager.cpp \
               plugins/pluginitem.cpp \
               modes/modemanager.cpp \
               modes/modewidget.cpp \
               modes/modetabbar.cpp \
               argumentparser.cpp \
               jsonsettings.cpp \
               mainwindow.cpp

HEADERS     += profiles/profilemanager.h \
               profiles/profiledialog.h \
               plugins/pluginmanager.h \
               plugins/pluginitem.h \
               plugins/iplugin.h \
               modes/modemanager.h \
               modes/modewidget.h \
               modes/modetabbar.h \
               modes/imode.h \
               argumentparser.h \
               core_constants.h \
               jsonsettings.h \
               core_global.h \
               mainwindow.h

INCLUDEPATH += $$PWD

FORMS       += profiles/profiledialog.ui

RESOURCES   += core.qrc
