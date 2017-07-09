#include "androidusbdriver.h"

androidUsbDriver::androidUsbDriver(QWidget *parent) : unixUsbDriver(parent)
{
    qDebug() << "androidUsbDriver object created!";
    mainActivity = QtAndroid::androidActivity();
}

androidUsbDriver::~androidUsbDriver(void){
    qDebug() << "\n\nandroidUsbDriver destructor ran!";
    mainActivity.callMethod<void>("closeDevice");
}

unsigned char androidUsbDriver::usbInit(unsigned long VIDin, unsigned long PIDin){
    qDebug() << "Entering androidUsbDriver::usbInit";

    mainActivity.callMethod<void>("nonStaticTest");

    qDebug() << "If you cannot see 'nonStaticTest' above, then the _______JAVA CLASS DOES NOT EXIST____";


    mainActivity.callMethod<void>("findDevice");

    QAndroidJniObject usbfs_path_java = mainActivity.getObjectField<jstring>("usbfs_path");
    QString usbfs_path_qstring = usbfs_path_java.toString();
    char *usbfs_path = usbfs_path_qstring.toUtf8().data();

    jint file_descriptor_java = mainActivity.getField<jint>("file_descriptor");
    int file_descriptor = (int)file_descriptor_java;

    qDebug() << "usbfs path = " << usbfs_path;
    qDebug() << "file descriptor = " << file_descriptor;

    if(file_descriptor == -69){
        qDebug() << "DEVICE NOT DETECTED";
        return -69;
    }

    int error = libusb_init(&ctx);
    if(error){
        qDebug() << "libusb_init FAILED";
        return error;
    } else qDebug() << "Libusb context initialised";

    libusb_set_debug(ctx, 3);

    qDebug() << "Opening Device!";
    libusb_device * device_ptr = libusb_get_device2(ctx, usbfs_path);
    error = libusb_open2(device_ptr, &handle, file_descriptor);
    if(error){
        qDebug() << "ERROR OPENING DEVICE";
        return error;
    }
    qDebug() << "Device Found!!";
    /*qDebug("Looking for device %x:%x", VIDin, PIDin);
    handle = libusb_open_device_with_vid_pid(ctx, VIDin, PIDin);
    if(handle==NULL){
        qDebug() << "DEVICE NOT FOUND";
        return -1;
    }
    qDebug() << "Device found!!";
*/
    qDebug() << (libusb_kernel_driver_active(handle, 0) ? "KERNEL DRIVER ACTIVE" : "KERNEL DRIVER INACTIVE");
    if(libusb_kernel_driver_active(handle, 0)){
        libusb_detach_kernel_driver(handle, 0);
    }
    error = libusb_claim_interface(handle, 0);
    if(error){
        qDebug() << "libusb_claim_interface FAILED";
        qDebug() << "ERROR" << error << libusb_error_name(error);
        return error;
    } else qDebug() << "Interface claimed!";

    return 0;
}

int winUsbDriver::flashFirmware(void){
    char fname[64];
    qDebug() << "\n\n\n\n\n\n\n\nFIRMWARE MISMATCH!!!!  FLASHING....\n\n\n\n\n\n\n";
    sprintf(fname, "labrafirm_%04x_%02x.hex", EXPECTED_FIRMWARE_VERSION, DEFINED_EXPECTED_VARIANT);
    qDebug() << "FLASHING " << fname;

    bootloaderJump();
    mainActivity.callMethod<void>("closeDevice");

    QThread::msleep(2000);

    mainActivity.callMethod<void>("findDevice_bootloader");

    //assets:/firmware

    //Set up interface to dfuprog
    QString dfuprog_location = QCoreApplication::applicationDirPath();
    dfuprog_location.append("/firmware/dfu-programmer");
    QString file_location = QCoreApplication::applicationDirPath();
    file_location.append("/firmware/");
    file_location.append(fname);
    QProcess dfu_exe;
    QStringList args_stage1;
    args_stage1 << "atxmega32a4u" << "erase" << "--force";
    QStringList args_stage2;
    args_stage2 << "atxmega32a4u" << "flash" << file_location;
    QStringList args_stage3;
    args_stage3 << "atxmega32a4u" << "launch";
    QStringList args_stage4;
    args_stage4 << "atxmega32a4u" << "launch";

    //Run stage 1
    dfu_exe.start(dfuprog_location, args_stage1);
    dfu_exe.waitForFinished(-1);
    qDebug() << "stdio_stage1" << dfu_exe.readAllStandardOutput();
    qDebug() << "sterr_stage1" << dfu_exe.readAllStandardError();
    qDebug() << "EXIT_CODE stage1" << dfu_exe.exitCode();
    if(dfu_exe.exitCode()){
        return dfu_exe.exitCode()+100;
    }

    //Run stage 2
    dfu_exe.start(dfuprog_location, args_stage2);
    dfu_exe.waitForFinished(-1);
    qDebug() << "stdio_stage2" << dfu_exe.readAllStandardOutput();
    qDebug() << "sterr_stage2" << dfu_exe.readAllStandardError();
    qDebug() << "EXIT_CODE stage2" << dfu_exe.exitCode();
    if(dfu_exe.exitCode()){
        return dfu_exe.exitCode()+200;
    }

    //Run stage 3
    dfu_exe.start(dfuprog_location, args_stage3);
    dfu_exe.waitForFinished(-1);
    qDebug() << "stdio_stage3" << dfu_exe.readAllStandardOutput();
    qDebug() << "sterr_stage3" << dfu_exe.readAllStandardError();
    qDebug() << "EXIT_CODE stage3" << dfu_exe.exitCode();
    if(dfu_exe.exitCode()){
        return dfu_exe.exitCode()+300;
    }

    QThread::msleep(2000);

    //Run stage 4 - double launch to clear the eeprom flag from bootloaderJump.
    dfu_exe.start(dfuprog_location, args_stage4);
    dfu_exe.waitForFinished(-1);
    qDebug() << "stdio_stage4" << dfu_exe.readAllStandardOutput();
    qDebug() << "sterr_stage4" << dfu_exe.readAllStandardError();
    qDebug() << "EXIT_CODE stage4" << dfu_exe.exitCode();
    return 0;
}

