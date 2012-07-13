include(../../../kittyim.pri)

TARGET    = core
DESTDIR   = $$BIN_PATH
TEMPLATE  = lib

DEFINES  += CORE_LIBRARY

SOURCES  += plugins/manager.cpp \
    argumentparser.cpp \
    profiles/profilemanager.cpp \
    dialogs/profiledialog.cpp

HEADERS  += core_global.h \
            plugins/manager.h \
            plugins/iplugin.h \
            plugins/plugininfo.h \
    argumentparser.h \
    profiles/profilemanager.h \
    dialogs/profiledialog.h

INCLUDEPATH += $$PWD

FORMS += \
    dialogs/profiledialog.ui

RESOURCES += \
    core.qrc
