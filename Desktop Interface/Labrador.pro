#-------------------------------------------------
#
# Project created by QtCreator 2016-03-30T13:27:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Labrador
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    buffercontrol.cpp \
    esposlider.cpp \
    espospinbox.cpp \
    espocombobox.cpp \
    functiongencontrol.cpp \
    isodriver.cpp \
    isobuffer.cpp \
    siprint.cpp \
    noclosemenu.cpp \
    cursorenabler.cpp \
    desktop_settings.cpp \
    deviceconnecteddisplay.cpp \
    timedtickbox.cpp \
    scoperangeenterdialog.cpp \
    voltagespinbox.cpp \
    genericusbdriver.cpp \

HEADERS  += mainwindow.h \
    qcustomplot.h \
    buffercontrol.h \
    esposlider.h \
    espospinbox.h \
    espocombobox.h \
    functiongencontrol.h \
    xmega.h \
    isodriver.h \
    isobuffer.h \
    desktop_settings.h \
    siprint.h \
    noclosemenu.h \
    cursorenabler.h \
    deviceconnecteddisplay.h \
    timedtickbox.h \
    scoperangeenterdialog.h \
    voltagespinbox.h \
    genericusbdriver.h \

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
unix:!macx:SOURCES += gahnooslashlinuxusbdriver.cpp
unix:!macx:HEADERS += gahnooslashlinuxusbdriver.h

#libusb include
#unix:!macx:LIBS += -lusb-1.0

#libusb1 include

