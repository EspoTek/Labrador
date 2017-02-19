#-------------------------------------------------
#
# Project created by QtCreator 2016-03-30T13:27:52
#
#-------------------------------------------------


############################################################################
######CLEAN->RUN QMAKE->BUILD after changing anything on this page!!!######
##########################################################################

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Labrador
TEMPLATE = app

QCP_VER = 1
DEFINES += "QCP_VER=$${QCP_VER}"
equals(QCP_VER,"2"){
    DEFINES += QCUSTOMPLOT_USE_OPENGL
    message("Using QCP2 with OpenGL support")
}

include(ui_elements.pri)

MOC_DIR = $$PWD/moc

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

INCLUDEPATH += $$PWD/ui_elements
DEPENDPATH += $$PWD/ui_elements


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

unix:!android:!macx:INCLUDEPATH += $$PWD/build_linux

#libusb include
unix:!android:!macx:LIBS += -Lbuild_linux/libusb -lusb-1.0  ##I suspect the -L here does nothing!
unix:!android:!macx:INCLUDEPATH += build_linux/libusb
unix:!android:!macx:DEPENDPATH += build_linux/libusb

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

#############################################################
#################    ANDROID BUILD ONLY    #################
###########################################################

android:{
    QMAKE_CXXFLAGS += -Dlog2\(x\)=\(log\(x\)/1.4426950408889634\)
    #Android doesn't support log2() by default...
    #http://stackoverflow.com/questions/11080118/does-android-support-log2.  Good idea, Ray!
    QMAKE_CFLAGS += fsigned-char
    #Android treats char as unsigned by default (why???)

    QT += androidextras
    CONFIG += mobility
    MOBILITY =

    INCLUDEPATH += $$PWD/build_android
    SOURCES += androidusbdriver.cpp
    HEADERS += androidusbdriver.h
    INCLUDEPATH += $$PWD/build_android/libusb-martin-kuldeep
    DEPENDPATH += $$PWD/build_android/libusb-martin-kuldeep

    ANDROID_PACKAGE_SOURCE_DIR  = $$PWD/build_android/package_source
    assets_deploy.files=$$files($$PWD/build_android/package_source/assets/*)
    assets_deploy.path=/assets
    INSTALLS += asssets_deploy


    DISTFILES += \
        build_android/package_source/AndroidManifest.xml \
        build_android/package_source/gradle/wrapper/gradle-wrapper.jar \
        build_android/package_source/gradlew \
        build_android/package_source/res/values/libs.xml \
        build_android/package_source/build.gradle \
        build_android/package_source/gradle/wrapper/gradle-wrapper.properties \
        build_android/package_source/gradlew.bat \
        build_android/package_source/AndroidManifest.xml \
        build_android/package_source/res/values/libs.xml \
        build_android/package_source/build.gradle \
        build_android/package_source/src/androidInterface.java

    equals(ANDROID_TARGET_ARCH, armeabi-v7a){
        message("qmake building for Android (ARM) platform")
        LIBS += -L$${PWD}\build_android\libusb-martin-kuldeep\android\armeabi-v7a -lusb1.0
        ANDROID_EXTRA_LIBS += $${PWD}\build_android\libusb-martin-kuldeep\android\armeabi-v7a/libusb1.0.so
        }
    equals(ANDROID_TARGET_ARCH, x86){
        message("qmake building for Android (x86) platform")
        LIBS += -L$$PWD/build_android/libusb-martin-kuldeep/android/x86 -lusb1.0
        ANDROID_EXTRA_LIBS += $$PWD/build_android/libusb-martin-kuldeep/android/x86/libusb1.0.so
        }
}

DISTFILES += \
    build_android/package_source/AndroidManifest.xml \
    build_android/package_source/gradle/wrapper/gradle-wrapper.jar \
    build_android/package_source/gradlew \
    build_android/package_source/res/values/libs.xml \
    build_android/package_source/build.gradle \
    build_android/package_source/gradle/wrapper/gradle-wrapper.properties \
    build_android/package_source/gradlew.bat
