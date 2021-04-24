#-------------------------------------------------
#
# Project created by QtCreator 2016-03-30T13:27:52
#
#-------------------------------------------------


############################################################################
######CLEAN->RUN QMAKE->BUILD after changing anything on this page!!!######
##########################################################################

QT += core gui

CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Labrador
TEMPLATE = app


!contains(CONFIG, "USE_SYSTEM_QCP") {
    message("Using bundled version of qcustomplot")
    QCP_VER = 1
} else {
    message("Using system version of qcustomplot")
    DEFINES += QCUSTOMPLOT_USE_OPENGL
    QCP_VER = 2
    LIBS += -lqcustomplot
}


DEFINES += "QCP_VER=$${QCP_VER}"
equals(QCP_VER,"2"){
    DEFINES += QCUSTOMPLOT_USE_OPENGL
    win32: LIBS += -lOpenGL32
    message("Using QCP2 with OpenGL support")
}

include(ui_elements.pri)

MOC_DIR = $$PWD/moc

SOURCES += main.cpp\
    DisplayControl.cpp \
        mainwindow.cpp \
    functiongencontrol.cpp \
    isodriver.cpp \
    isobuffer.cpp \
    desktop_settings.cpp \
    pinoutDialog.cpp \
    scoperangeenterdialog.cpp \
    genericusbdriver.cpp \
    isobufferbuffer.cpp \
    uartstyledecoder.cpp \
    daqform.cpp \
    daqloadprompt.cpp \
    isobuffer_file.cpp \
	i2cdecoder.cpp

HEADERS  += mainwindow.h \
    DisplayControl.h \
    functiongencontrol.h \
    pinoutDialog.h \
    xmega.h \
    isodriver.h \
    isobuffer.h \
    desktop_settings.h \
    scoperangeenterdialog.h \
    genericusbdriver.h \
    isobufferbuffer.h \
    q_debugstream.h \
    unified_debug_structure.h \
    uartstyledecoder.h \
    daqform.h \
    daqloadprompt.h \
    isobuffer_file.h \
	i2cdecoder.h

android:{
FORMS    += ui_files_mobile/mainwindow.ui \
    ui_files_mobile/scoperangeenterdialog.ui \
    ui_files_desktop/daqform.ui \
    ui_files_desktop/daqloadprompt.ui
}

!android:{
FORMS    += ui_files_desktop/mainwindow.ui \
    ui_files_desktop/scoperangeenterdialog.ui \
    ui_files_desktop/daqform.ui \
    ui_files_desktop/daqloadprompt.ui
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
        DEFINES += "WINDOWS_32_BIT"
    } else {
        message("Building for Windows (x64)")
        CONFIG(release, debug|release): LIBS += -L$$PWD/build_win/libusbk/bin/lib/amd64/ -llibusbK
        else:CONFIG(debug, debug|release): LIBS += -L$$PWD/build_win/libusbk/bin/lib/amd64/ -llibusbK
        DEFINES += "WINDOWS_64_BIT"
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
    LIBS += -lusb-1.0 ##make sure you have the libusb-1.0-0-dev package!
    LIBS += -ldfuprog-0.9

    QMAKE_CXXFLAGS+=-O2

    contains(QT_ARCH, arm) {
            message("Building for Raspberry Pi")

            #All ARM-Linux GCC treats char as unsigned by default???
            QMAKE_CFLAGS += -fsigned-char
            QMAKE_CXXFLAGS += -fsigned-char
            DEFINES += "PLATFORM_RASPBERRY_PI"

            !contains(CONFIG, "USE_SYSTEM_LIBS") {
                LIBS += -L$$PWD/build_linux/libdfuprog/lib/arm
                lib_deploy.files = $$PWD/build_linux/libdfuprog/lib/arm/libdfuprog-0.9.so
            }

    } else {
        contains(QT_ARCH, i386) {
            message("Building for Linux (x86)")

            !contains(CONFIG, "USE_SYSTEM_LIBS") {
                LIBS += -L$$PWD/build_linux/libdfuprog/lib/x86
                lib_deploy.files = $$PWD/build_linux/libdfuprog/lib/x86/libdfuprog-0.9.so
            }
        } else {
            message("Building for Linux (x64)")
            !contains(CONFIG, "USE_SYSTEM_LIBS") {
                LIBS += -Lbuild_linux/libusb  ##I suspect the -L here does nothing!
                #libdfuprog include
                LIBS += -L$$PWD/build_linux/libdfuprog/lib/x64
                lib_deploy.files = $$PWD/build_linux/libdfuprog/lib/x64/libdfuprog-0.9.so
            }
        }
    }

    contains(CONFIG, "USE_SYSTEM_LIBS") {
        INCLUDEPATH += $$[QT_INSTALL_PREFIX]/include/libusb-1.0
    } else {
        INCLUDEPATH += build_linux/libusb
        DEPENDPATH += build_linux/libusb

        #libdfuprog include
        INCLUDEPATH += $$PWD/build_linux/libdfuprog/include
        DEPENDPATH += $$PWD/build_linux/libdfuprog/include

        lib_deploy.path = /usr/lib
        INSTALLS += lib_deploy
    }

    other.files += bin/firmware
    other.files += bin/waveforms
    other.path = /usr/bin/EspoTek-Labrador
    
    target.path = /usr/bin/EspoTek-Labrador
    
    udev.path = /etc/udev/rules.d
    udev.files = rules.d/69-labrador.rules
    
    icon48.files += resources/icon48/espotek-labrador.png
    icon48.path = /usr/share/icons/hicolor/48x48/apps/

    icon256.files += resources/icon256/espotek-labrador.png
    icon256.path = /usr/share/icons/hicolor/256x256/apps/
    
    equals(APPIMAGE, 1){
        desktop.files += resources/appimage/espotek-labrador.desktop
    }
    !equals(APPIMAGE, 1){
        desktop.files += resources/espotek-labrador.desktop
    }
    desktop.path = /usr/share/applications
    
    symlink.path = /usr/bin
    symlink.extra = ln -sf ${INSTALL_ROOT}/usr/bin/EspoTek-Labrador/Labrador /usr/bin/labrador
    
    udevextra.path = /etc/udev/rules.d
    !equals(DEB, 1){
        udevextra.extra = udevadm control --reload-rules && udevadm trigger
    }

    equals(APPIMAGE, 1){
        other.path = /usr/bin
        target.path = /usr/bin
    }

    INSTALLS += target
    INSTALLS += other
    INSTALLS += udev
    INSTALLS += icon48
    INSTALLS += icon256
    INSTALLS += desktop

    !equals(APPIMAGE, 1){
        INSTALLS += symlink
        INSTALLS += udevextra
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
#################    ANDROID BUILD ONLY    #################
###########################################################

android:{
    QMAKE_CFLAGS += -fsigned-char
    QMAKE_CXXFLAGS += -fsigned-char
    #Android treats char as unsigned by default (why???)

    # Building .so files fails with -Wl,--no-undefined
    QMAKE_LFLAGS_APP     -= -Wl,--no-undefined
    QMAKE_LFLAGS_SHLIB   -= -Wl,--no-undefined
    QMAKE_LFLAGS_PLUGIN  -= -Wl,--no-undefined
    QMAKE_LFLAGS_NOUNDEF -= -Wl,--no-undefined

    QT += androidextras
    CONFIG += mobility
    MOBILITY =

    INCLUDEPATH += $$PWD/build_android
    SOURCES += androidusbdriver.cpp
    HEADERS += androidusbdriver.h
    INCLUDEPATH += $$PWD/build_android/libusb-242
    DEPENDPATH += $$PWD/build_android/libusb-242

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

    # Doing the following inside one equals() failed. qmake bug?  https://forum.qt.io/topic/113836/dynamic-libs-on-android-with-qt5-14-2/4
    for(abi, ANDROID_ABIS): message("qmake building for Android ($${abi}) platform")
    for(abi, ANDROID_ABIS): LIBS += -L$${PWD}/build_android/libusb-242/android/$${abi} -lusb1.0
    for(abi, ANDROID_ABIS): ANDROID_EXTRA_LIBS += $${PWD}/build_android/libusb-242/android/$${abi}/libusb1.0.so
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
