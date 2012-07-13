include(../../kittyim.pri)
include(../../src/libs/core/core.pri)

QT       += testlib
QT       -= gui

TARGET    = tst_plugininfotest
CONFIG   += console testcase qtestlib
CONFIG   -= app_bundle

TEMPLATE  = app

SOURCES  += tst_plugininfo.cpp \
            tst_argumentparser.cpp
