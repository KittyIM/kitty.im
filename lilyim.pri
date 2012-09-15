!isEmpty(LILYIM_PRI):error("lilyim.pri already included")
LILYIM_PRI = 1

BIN_PATH     = $$PWD/bin
SRC_PATH     = $$PWD/src
PLUGIN_PATH  = $$BIN_PATH/plugins

LIBS        *= -L$$BIN_PATH

INCLUDEPATH += $$SRC_PATH $$SRC_PATH/plugins $$SRC_PATH/libs
