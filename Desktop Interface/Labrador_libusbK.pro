#-------------------------------------------------
#
# Project created by QtCreator 2016-03-30T13:27:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Labrador_libusbk
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    buffercontrol.cpp \
    esposlider.cpp \
    espospinbox.cpp \
    winusbdriver.cpp \
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
    genericusbdriver.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    buffercontrol.h \
    esposlider.h \
    espospinbox.h \
    winusbdriver.h \
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
    genericusbdriver.h

FORMS    += mainwindow.ui \
    scoperangeenterdialog.ui

RESOURCES += \
    resources.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libusbk/bin/lib/amd64/ -llibusbK
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libusbk/bin/lib/amd64/ -llibusbK

INCLUDEPATH += $$PWD/libusbk/includes
DEPENDPATH += $$PWD/libusbk/includes


DESTDIR = bin

RC_ICONS = appicon.ico
