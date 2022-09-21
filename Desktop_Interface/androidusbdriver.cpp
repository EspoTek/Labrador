#include "androidusbdriver.h"
#include "QStandardPaths"

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

    //QAndroidJniObject usbfs_path_java = mainActivity.getObjectField<jstring>("usbfs_path");
    //QString usbfs_path_qstring = usbfs_path_java.toString();
    //char *usbfs_path = usbfs_path_qstring.toUtf8().data();

    QAndroidJniObject usbfs_path_java = mainActivity.getObjectField<jstring>("usbfs_path");
    QString usbfs_path_qstring = usbfs_path_java.toString();
    std::string usbfs_path_stdstr = usbfs_path_qstring.toStdString();
    char usbfs_path[128];
    strcpy(usbfs_path, usbfs_path_stdstr.c_str());

    jint file_descriptor_java = mainActivity.getField<jint>("file_descriptor");
    int file_descriptor = (int)file_descriptor_java;

    qDebug() << "usbfs path = " << usbfs_path;
    qDebug() << "file descriptor = " << file_descriptor;

    if(file_descriptor == -69){
        qDebug() << "DEVICE NOT DETECTED";
        return -69;
    } else if(file_descriptor == -65) {
        qDebug() << "DEVICE DETECTED IN BOOTLOADER MODE";
        return E_BOARD_IN_BOOTLOADER;
    }

    int error = libusb_init(&ctx);
    if(error){
        qDebug() << "libusb_init FAILED";
        return error;
    } else qDebug() << "Libusb context initialised";

    libusb_set_debug(ctx, 3);

    qDebug() << "Opening Device!";
    //libusb_device * device_ptr = libusb_get_device2(ctx, usbfs_path);
    //error = libusb_open2(device_ptr, &handle, file_descriptor);
    error = libusb_wrap_fd(ctx, file_descriptor, &handle);
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

int androidUsbDriver::get_new_bootloader_ctx(libusb_device **device_ptr, libusb_device_handle **handle, libusb_context **ctx){

    *(ctx) = NULL;
    *(handle) = NULL;
    *(device_ptr) = NULL;

    mainActivity.callMethod<void>("closeDevice");
    //Find device in Java
    mainActivity.callMethod<void>("findDevice_bootloader");
    QAndroidJniObject usbfs_path_java = mainActivity.getObjectField<jstring>("usbfs_path");
    QString usbfs_path_qstring = usbfs_path_java.toString();
    std::string usbfs_path_stdstr = usbfs_path_qstring.toStdString();
    char usbfs_path[128];
    strcpy(usbfs_path, usbfs_path_stdstr.c_str());
    jint file_descriptor_java = mainActivity.getField<jint>("file_descriptor");
    int file_descriptor = (int)file_descriptor_java;

    qDebug() << "usbfs path = " << usbfs_path;
    qDebug() << "file descriptor = " << file_descriptor;

    //Initialise libusb-martin-kuldeep
    int error = libusb_init(ctx);
    if(error){
        qDebug() << "libusb_init FAILED";
        return error;
    } else qDebug() << "Libusb context initialised";

    libusb_set_debug(*(ctx), 3);

    qDebug() << "Opening Device!";

    //*(device_ptr) = libusb_get_device2(*(ctx), usbfs_path);
    //error = libusb_open2(*(device_ptr), handle, file_descriptor);
    error = libusb_wrap_fd(*(ctx), file_descriptor, handle);
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
    qDebug() << (libusb_kernel_driver_active(*(handle), 0) ? "KERNEL DRIVER ACTIVE" : "KERNEL DRIVER INACTIVE");
    if(libusb_kernel_driver_active(*(handle), 0)){
        libusb_detach_kernel_driver(*(handle), 0);
    }
    error = libusb_claim_interface(*(handle), 0);
    if(error){
        qDebug() << "libusb_claim_interface FAILED";
        qDebug() << "ERROR" << error << libusb_error_name(error);
        return error;
    } else qDebug() << "Interface claimed!";

    return 0;
}

int androidUsbDriver::flashFirmware(void){

    qDebug() << "\n\n\n\n\n\n\n\nFLASHING FIRMWARE....\n\n\n\n\n\n\n";

    //Copy to somewhere that fopen can access
    QFile asset_file(QString::asprintf("assets:/firmware/labrafirm_%04x_%02x.hex", EXPECTED_FIRMWARE_VERSION, DEFINED_EXPECTED_VARIANT));
    qDebug() << "FLASHING " << asset_file.fileName();
    qDebug() << "asset_file.exists()" << asset_file.exists();

     QString filePath = QStandardPaths::writableLocation( QStandardPaths::StandardLocation::AppDataLocation );
     filePath.append( "/firmware.hex");
     if (asset_file.exists()) {
         if( QFile::exists( filePath ) ){
             qDebug() << "File already exists in temporary path.  Removing....";
             QFile::remove( filePath );
         }

         if( asset_file.copy( filePath ) ){
             QFile::setPermissions( filePath, QFile::WriteOwner | QFile::ReadOwner );
            qDebug() << "firmware temp file copied to" << filePath;
         } else {
             qDebug() << "\n\n\nERROR: COULD NOT CREATE TEMP FIRMWARE FILE\n\n\n";
         }
     } else qDebug() << "File not found in assets";

    if(connected) {
        //Switch from application mode to bootloader mode.  Otherwise assume we are in bootloader.
        bootloaderJump();
        mainActivity.callMethod<void>("closeDevice");
        libusb_release_interface(handle, 0);
        libusb_close(handle);
        libusb_exit(ctx);

        qDebug() << "BA94 closed";

        QThread::msleep(2000);
}

    //Initialise libusb-martin-kuldeep
    libusb_context *ctx;
    libusb_device * device_ptr;
    libusb_device_handle *handle;
    int error = get_new_bootloader_ctx(&device_ptr, &handle, &ctx);
    if(error){
            qDebug() << "get_new_bootloader_ctx FAILED";
            return 69;
    }

    /*
    //Extract bus/device number
    usbfs_path[16] = NULL;
    char *busNumber = &usbfs_path[13];
    char *devNumber = &usbfs_path[17];

    qDebug() << "Thingo thinks it's octal!!";
    qDebug() << busNumber;
    qDebug() << devNumber;

    qDebug() << "Remove those leading zeros";

    for (int i=0; i<3; i++){
        if(busNumber[0] == '0') busNumber++;
        if(devNumber[0] == '0') devNumber++;
    }

    qDebug() << "Here we go!";

    qDebug() << busNumber;
    qDebug() << devNumber;
*/

    //Set up interface to dfuprog
    int exit_code;
    char command1[256];
    sprintf(command1, "dfu-programmer atxmega32a4u erase --force --debug 300");
    char command2[256];
    sprintf(command2, "dfu-programmer atxmega32a4u flash %s --debug 300", qPrintable(filePath));
    char command3[256];
    sprintf(command3, "dfu-programmer atxmega32a4u launch");
    char command4[256];
    sprintf(command4, "dfu-programmer atxmega32a4u launch");

    qDebug() << "\n\nFlashing Firmware, stage 1.\n\n";

    //Run stage 1
    exit_code = dfuprog_virtual_cmd(command1, device_ptr, handle, ctx,  0);
    if(exit_code){
        qDebug() << "ERROR ERASING FIRMWARE.";
        //return exit_code+100;
    }

    error = get_new_bootloader_ctx(&device_ptr, &handle, &ctx);
    if(error){
            qDebug() << "\n\n\nget_new_bootloader_ctx FAILED\n\n\n";
            return 169;
    }

    qDebug() << "\n\nFlashing Firmware, stage 2.\n\n";

    //Run stage 2
    exit_code = dfuprog_virtual_cmd(command2, device_ptr, handle, ctx,  0);
    if(exit_code){
        qDebug() << "\n\n\nERROR WRITING NEW FIRMWARE TO DEVICE.\n\n\n";
        //return exit_code+200;
    }

    error = get_new_bootloader_ctx(&device_ptr, &handle, &ctx);
    if(error){
            qDebug() << "get_new_bootloader_ctx FAILED";
            return 269;
    }

    qDebug() << "\n\nFlashing Firmware, stage 3.\n\n";

    //Run stage 3
    exit_code = dfuprog_virtual_cmd(command3, device_ptr, handle, ctx,  0);
    if(exit_code){
        qDebug() << "\n\n\nERROR LAUNCHING DEVICE (INITIAL).\n\n\n";
       //return exit_code+300;
    }

    QThread::msleep(2000);

    error = get_new_bootloader_ctx(&device_ptr, &handle, &ctx);
    if(error){
            qDebug() << "get_new_bootloader_ctx FAILED";
            return 369;
    }

    qDebug() << "\n\nFlashing Firmware, stage 4.\n\n";

    //Run stage 4 - double launch to clear the eeprom flag from bootloaderJump.
    exit_code = dfuprog_virtual_cmd(command4, device_ptr, handle, ctx,  0);
    if(exit_code){
        qDebug() << "\n\n\nERROR LAUNCHING DEVICE (SECONDARY).\n\n\n";
       //return exit_code+300;
    }
    mainActivity.callMethod<void>("closeDevice");
    return 0;
}
