#-------------------------------------------------
#
# Project created by QtCreator 2018-03-28T13:51:09
#
#-------------------------------------------------

QT       += core gui widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = librademo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        ../../../../Desktop_Interface/ui_elements/qcp1/qcustomplot.cpp \
        ../../librador_shared_library/librador.cpp \
        ../../librador_shared_library/o1buffer.cpp \
        ../../librador_shared_library/usbcallhandler.cpp \


HEADERS += \
        mainwindow.h \
        ../../../../Desktop_Interface/ui_elements/qcp1/qcustomplot.h

INCLUDEPATH += \
        ../../../../Desktop_Interface/ui_elements/qcp1


FORMS += \
        mainwindow.ui

LIBS += -llibusb-1.0
INCLUDEPATH += ../../librador_shared_library
DEPENDPATH += ../../librador_shared_library

