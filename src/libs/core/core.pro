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
               mainwindow.cpp \
			   actions/actionmanager.cpp \
			   settings/settingsdialog.cpp \
			   settings/generalsettings.cpp \
			   settings/connectionsettings.cpp \
			   icore.cpp \
			   console/consoledialog.cpp \
			   console/debugconsole.cpp \
			   console/commandconsole.cpp \
			   icons/icontheme.cpp \
			   icons/iconmanager.cpp \
			   console/iconconsole.cpp \
    trayicon.cpp \
    settings/mainwindowsettings.cpp

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
               mainwindow.h \
			   actions/actionmanager.h \
			   settings/settingsdialog.h \
			   settings/isettingspage.h \
			   settings/generalsettings.h \
			   settings/connectionsettings.h \
			   icore.h \
			   console/iconsoletab.h \
			   console/consoledialog.h \
			   console/debugconsole.h \
			   console/commandconsole.h \
			   icons/iconmanager.h \
			   icons/icontheme.h \
			   console/iconconsole.h \
    trayicon.h \
    settings/mainwindowsettings.h

INCLUDEPATH += $$PWD

FORMS       += profiles/profiledialog.ui \
			   settings/generalsettingswidget.ui \
			   settings/connectionsettingswidget.ui \
    settings/mainwindowsettingswidget.ui

RESOURCES   += core.qrc
