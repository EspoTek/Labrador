#ifndef unixUsbDriver_H
#define unixUsbDriver_H

#include <QWidget>
#include <QThread>
#include <QMutex>
#include <QDateTime>

#include "unixusbdriver.h"
#include "libusb.h"

class androidUsbDriver : public unixUsbDriver
{
    Q_OBJECT
private:
    //Generic Functions
    unsigned char usbInit(unsigned long VIDin, unsigned long PIDin);
};

#endif // unixUsbDriver_H
