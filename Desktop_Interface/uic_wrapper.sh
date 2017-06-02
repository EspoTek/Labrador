#!/bin/sh
LD_LIBRARY_PATH=/home/esposch/qt5_source/qt5/qtbase/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}
export LD_LIBRARY_PATH
QT_PLUGIN_PATH=/home/esposch/qt5_source/qt5/qtbase/plugins${QT_PLUGIN_PATH:+:$QT_PLUGIN_PATH}
export QT_PLUGIN_PATH
exec /home/esposch/qt5_source/qt5/qtbase/bin/uic "$@"
