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
               argumentparser.cpp \
               jsonsettings.cpp \
    mainwindow.cpp \
    plugins/pluginitem.cpp \
    modes/modemanager.cpp \
    modes/modewidget.cpp \
    modes/modetabbar.cpp

HEADERS     += profiles/profilemanager.h \
               profiles/profiledialog.h \
               plugins/manager.h \
               plugins/iplugin.h \
               argumentparser.h \
               jsonsettings.h \
               core_constants.h \
               core_global.h \
    mainwindow.h \
    plugins/pluginitem.h \
    modes/imode.h \
    modes/modemanager.h \
    modes/modewidget.h \
    modes/modetabbar.h

INCLUDEPATH += $$PWD

FORMS       += profiles/profiledialog.ui

RESOURCES   += core.qrc
