include(../../../kittyim.pri)
include(../../libs/core/core.pri)

TARGET   = im
DESTDIR  = $$PLUGIN_PATH
TEMPLATE = lib
CONFIG	+= dll

DEFINES += IM_LIBRARY

SOURCES += plugin.cpp \
		   contacts/contactmanager.cpp

HEADERS += plugin.h \
		   contacts/contactmanager.h \
		   contacts/icontact.h \
		   global.h

TRANSLATIONS = translations/im_untranslated.ts translations/im_pl.ts

RESOURCES   += im.qrc
