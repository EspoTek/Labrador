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
        ../../../../Desktop_Interface/ui_elements/qcp1/qcustomplot.cpp


HEADERS += \
        mainwindow.h \
        ../../../../Desktop_Interface/ui_elements/qcp1/qcustomplot.h

INCLUDEPATH += \
        ../../../../Desktop_Interface/ui_elements/qcp1


FORMS += \
        mainwindow.ui


unix:LIBS += -L../../librador_shared_library -lrador
unix:INCLUDEPATH += ../../librador_shared_library
unix:DEPENDPATH += ../../librador_shared_library

unix:!android:!macx {
    #libusb include
    LIBS += -L../../../../Desktop_Interface/build_linux/libusb -lusb-1.0  ##I suspect the -L here does nothing!
    INCLUDEPATH += ../../../../Desktop_Interface/build_linux/libusb
    DEPENDPATH += ../../../../Desktop_Interface/build_linux/libusb

    #libdfuprog include
    LIBS += -L../../../../Desktop_Interface/build_linux/libdfuprog/lib/x64 -ldfuprog-0.9
    INCLUDEPATH += ../../../../Desktop_Interface/build_linux/libdfuprog/include
    DEPENDPATH += ../../../../Desktop_Interface/build_linux/libdfuprog/include

    #linux defines
    DEFINES += \
        PLATFORM_LINUX \
}

macx {
    #libusb include
    LIBS += -L../../../Desktop_Interface/build_mac/libusb/lib -lusb-1.0  ##I suspect the -L here does nothing!
    INCLUDEPATH += ../../../Desktop_Interface/build_mac/libusb/include/libusb-1.0
    DEPENDPATH += ../../../Desktop_Interface/build_mac/libusb/include/libusb-1.0

    #libdfuprog include
    LIBS += -L../../../Desktop_Interface/build_mac/libdfuprog/lib -ldfuprog-0.9
    INCLUDEPATH += ../../../Desktop_Interface/build_mac/libdfuprog/include
    DEPENDPATH += ../../../Desktop_Interface/build_mac/libdfuprog/include

    #linux defines
    DEFINES += \
        PLATFORM_MAC \
}

