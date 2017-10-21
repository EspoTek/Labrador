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

android:{
FORMS    += ui_files_mobile/mainwindow.ui \
    ui_files_mobile/scoperangeenterdialog.ui
}

!android:{
FORMS    += ui_files_desktop/mainwindow.ui \
    ui_files_desktop/scoperangeenterdialog.ui
}


RESOURCES += \
    resources.qrc

DESTDIR = bin

RC_ICONS = appicon.ico

INCLUDEPATH += $$PWD/ui_elements
DEPENDPATH += $$PWD/ui_elements


###########################################################
################    WINDOWS BUILD ONLY    ################
#########################################################

win32{
    INCLUDEPATH += $$PWD/build_win
    SOURCES += winusbdriver.cpp
    HEADERS += winusbdriver.h

    #libusbk include
    contains(QT_ARCH, i386) {
        message("Building for Windows (x86)")
        CONFIG(release, debug|release): LIBS += -L$$PWD/build_win/libusbk/bin/lib/x86/ -llibusbK
        else:CONFIG(debug, debug|release): LIBS += -L$$PWD/build_win/libusbk/bin/lib/x86/ -llibusbK
    } else {
        message("Building for Windows (x64)")
        CONFIG(release, debug|release): LIBS += -L$$PWD/build_win/libusbk/bin/lib/amd64/ -llibusbK
        else:CONFIG(debug, debug|release): LIBS += -L$$PWD/build_win/libusbk/bin/lib/amd64/ -llibusbK
    }
    INCLUDEPATH += $$PWD/build_win/libusbk/includes
    DEPENDPATH += $$PWD/build/win/libusbk/includes
    DEFINES += PLATFORM_WINDOWS
}

#############################################################
################    GNU/LINUX BUILD ONLY    ################
###########################################################

unix:!android:!macx{
    INCLUDEPATH += $$PWD/build_linux
    contains(QT_ARCH, arm) {
            message("Building for Raspberry Pi")
            #libusb include
            unix:!android:!macx:LIBS += -lusb-1.0  ##make sure you have the libusb-1.0-0-dev package!
            unix:!android:!macx:INCLUDEPATH += build_linux/libusb
            unix:!android:!macx:DEPENDPATH += build_linux/libusb

            #libdfuprog include
            unix:!android:!macx:LIBS += -L$$PWD/build_linux/libdfuprog/lib/arm -ldfuprog-0.9
            unix:!android:!macx:INCLUDEPATH += $$PWD/build_linux/libdfuprog/include
            unix:!android:!macx:DEPENDPATH += $$PWD/build_linux/libdfuprog/include
            QMAKE_CFLAGS += -fsigned-char
            QMAKE_CXXFLAGS += -fsigned-char
            DEFINES += "PLATFORM_RASPBERRY_PI"
            #All ARM-Linux GCC treats char as unsigned by default???
    } else {
        contains(QT_ARCH, i386) {
            message("Building for Linux (x86)")
            unix:!android:!macx:LIBS += -lusb-1.0  ##make sure you have the libusb-1.0-0-dev package!
            unix:!android:!macx:INCLUDEPATH += build_linux/libusb
            unix:!android:!macx:DEPENDPATH += build_linux/libusb

            #libdfuprog include
            unix:!android:!macx:LIBS += -L$$PWD/build_linux/libdfuprog/lib/x86 -ldfuprog-0.9
            unix:!android:!macx:INCLUDEPATH += $$PWD/build_linux/libdfuprog/include
            unix:!android:!macx:DEPENDPATH += $$PWD/build_linux/libdfuprog/include
        } else {
            message("Building for Linux (x64)")
            #libusb include
            unix:!android:!macx:LIBS += -Lbuild_linux/libusb -lusb-1.0  ##I suspect the -L here does nothing!
            unix:!android:!macx:INCLUDEPATH += build_linux/libusb
            unix:!android:!macx:DEPENDPATH += build_linux/libusb

            #libdfuprog include
            unix:!android:!macx:LIBS += -L$$PWD/build_linux/libdfuprog/lib/x64 -ldfuprog-0.9
            unix:!android:!macx:INCLUDEPATH += $$PWD/build_linux/libdfuprog/include
            unix:!android:!macx:DEPENDPATH += $$PWD/build_linux/libdfuprog/include
        }
    }
}



#############################################################
################    MAC OSX BUILD ONLY    ##################
###########################################################

macx:INCLUDEPATH += $$PWD/build_mac

#libusb dylib include
macx:LIBS += -L$$PWD/build_mac/libusb/lib -lusb-1.0
macx:INCLUDEPATH += $$PWD/build_mac/libusb/include/libusb-1.0
macx:DEPENDPATH += $$PWD/build_mac/libusb/include/libusb-1.0

#libdfuprog dylib include
macx:LIBS += -L$$PWD/build_mac/libdfuprog/lib -ldfuprog-0.9
macx:INCLUDEPATH += $$PWD/build_mac/libdfuprog/include
macx:DEPENDPATH += $$PWD/build_mac/libdfuprog/include

macx:QMAKE_LFLAGS += "-undefined dynamic_lookup"

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.10




#############################################################
########   SHARED UNIX-LIKE BUILDS (MAC + LINUX)   #########
###########################################################

unix:SOURCES += unixusbdriver.cpp
unix:HEADERS += unixusbdriver.h

#############################################################
########       SHARED ANDROID/LINUX GCC FLAGS      #########
###########################################################

unix:!macx: QMAKE_CXXFLAGS_RELEASE -= -O0
unix:!macx: QMAKE_CXXFLAGS_RELEASE -= -O1
unix:!macx: QMAKE_CXXFLAGS_RELEASE -= -O2
unix:!macx: QMAKE_CXXFLAGS_RELEASE -= -O3

android: QMAKE_CXXFLAGS_RELEASE -= -O0
android: QMAKE_CXXFLAGS_RELEASE -= -O1
android: QMAKE_CXXFLAGS_RELEASE -= -O2
android: QMAKE_CXXFLAGS_RELEASE -= -O3
android: QMAKE_CXXFLAGS_RELEASE -= -Os


android: QMAKE_CFLAGS_RELEASE -= -O0
android: QMAKE_CFLAGS_RELEASE -= -O1
android: QMAKE_CFLAGS_RELEASE -= -O2
android: QMAKE_CFLAGS_RELEASE -= -O3
android: QMAKE_CFLAGS_RELEASE -= -Os


#############################################################
#################    ANDROID BUILD ONLY    #################
###########################################################

android:{
    QMAKE_CFLAGS += -fsigned-char
    QMAKE_CXXFLAGS += -fsigned-char
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

    #libdfuprog include
    LIBS += -L$$PWD/build_android/libdfuprog/lib -ldfuprog-0.9
    INCLUDEPATH += $$PWD/build_android/libdfuprog/include
    DEPENDPATH += $$PWD/build_android/libdfuprog/include
    ANDROID_EXTRA_LIBS += $${PWD}/build_android/libdfuprog/lib/libdfuprog-0.9.so

    #liblog include
    LIBS += -L$$PWD/build_android/liblog/lib -llog
    ANDROID_EXTRA_LIBS += $${PWD}/build_android/liblog/lib/liblog.so



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
    build_android/package_source/gradlew.bat \
    build_android/package_source/AndroidManifest.xml \
    build_android/package_source/gradle/wrapper/gradle-wrapper.jar \
    build_android/package_source/gradlew \
    build_android/package_source/res/values/libs.xml \
    build_android/package_source/build.gradle \
    build_android/package_source/gradle/wrapper/gradle-wrapper.properties \
    build_android/package_source/gradlew.bat \
    build_android/package_source/res/xml/device_filter.xml
