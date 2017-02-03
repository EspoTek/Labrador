#-------------------------------------------------
#
# Project created by QtCreator 2016-03-30T13:27:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Labrador
TEMPLATE = app

include(ui_elements.pri)

SOURCES += main.cpp\
        mainwindow.cpp \
    functiongencontrol.cpp \
    isodriver.cpp \
    isobuffer.cpp \
    desktop_settings.cpp \
    scoperangeenterdialog.cpp \
    genericusbdriver.cpp \
    isobufferbuffer.cpp

HEADERS  += mainwindow.h \
    functiongencontrol.h \
    xmega.h \
    isodriver.h \
    isobuffer.h \
    desktop_settings.h \
    scoperangeenterdialog.h \
    genericusbdriver.h \
    isobufferbuffer.h \
    q_debugstream.h \
    unified_debug_structure.h

FORMS    += mainwindow.ui \
    scoperangeenterdialog.ui

RESOURCES += \
    resources.qrc

DESTDIR = bin

RC_ICONS = appicon.ico

###########################################################
################    WINDOWS BUILD ONLY    ################
#########################################################

win32:INCLUDEPATH += $$PWD/build_win
win32:SOURCES += winusbdriver.cpp
win32:HEADERS += winusbdriver.h

#libusbk include
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/build_win/libusbk/bin/lib/amd64/ -llibusbK
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/build_win/libusbk/bin/lib/amd64/ -llibusbK
win32:INCLUDEPATH += $$PWD/build_win/libusbk/includes
win32:DEPENDPATH += $$PWD/build/win/libusbk/includes

#############################################################
################    GNU/LINUX BUILD ONLY    ################
###########################################################

unix:!macx:INCLUDEPATH += $$PWD/build_linux

#libusb include
unix:!macx:LIBS += -Lbuild_linux/libusb -lusb-1.0  ##I suspect the -L here does nothing!
unix:!macx:INCLUDEPATH += build_linux/libusb
unix:!macx:DEPENDPATH += build_linux/libusb

#############################################################
################    MAC OSX BUILD ONLY    ##################
###########################################################

macx:INCLUDEPATH += $$PWD/build_mac

#libusb dylib include
macx:LIBS += -L$$PWD/build_mac/libusb/lib -lusb-1.0
macx:INCLUDEPATH += $$PWD/build_mac/libusb/include/libusb-1.0
macx:DEPENDPATH += $$PWD/build_mac/libusb/include/libusb-1.0

#############################################################
########   SHARED UNIX-LIKE BUILDS (MAC + LINUX)   #########
###########################################################

unix:SOURCES += unixusbdriver.cpp
unix:HEADERS += unixusbdriver.h

INCLUDEPATH += $$PWD/ui_elements
DEPENDPATH += $$PWD/ui_elements
