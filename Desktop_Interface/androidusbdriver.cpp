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
