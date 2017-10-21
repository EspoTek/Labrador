#ifndef androidUsbDriver_H
#define androidUsbDriver_H

#include <QWidget>
#include <QThread>
#include <QMutex>
#include <QDateTime>

#include "unixusbdriver.h"
#include "libusb.h"
#include <QAndroidJniObject>
#include <QtAndroid>


class androidUsbDriver : public unixUsbDriver
{
    Q_OBJECT
public:
    explicit androidUsbDriver(QWidget *parent = 0);
    ~androidUsbDriver();
private:
    //Generic Functions
    QAndroidJniObject mainActivity;
    unsigned char usbInit(unsigned long VIDin, unsigned long PIDin);
    int flashFirmware(void);
    int get_new_bootloader_ctx(libusb_device **device_ptr, libusb_device_handle **handle, libusb_context **ctx);
};

#endif // unixUsbDriver_H
