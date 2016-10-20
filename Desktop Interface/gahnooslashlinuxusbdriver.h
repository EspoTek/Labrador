#ifndef GAHNOOSLASHLINUXUSBDRIVER_H
#define GAHNOOSLASHLINUXUSBDRIVER_H

#include <QWidget>

#include "genericusbdriver.h"
#include "libusb.h"


class gahnooSlashLinuxUsbDriver : public genericUsbDriver
{
    Q_OBJECT
public:
    explicit gahnooSlashLinuxUsbDriver(QWidget *parent = 0);
    ~gahnooSlashLinuxUsbDriver();
    void usbSendControl(uint8_t RequestType, uint8_t Request, uint16_t Value, uint16_t Index, uint16_t Length, unsigned char *LDATA);
    char *isoRead(unsigned int *newLength);
private:
    //USB Vars
    libusb_context *ctx;
    libusb_device_handle *handle;
    unsigned char pipeID = 0x83;
    //USBIso Vars
    libusb_transfer *isoCtx[NUM_FUTURE_CTX];
    unsigned char dataBuffer[NUM_FUTURE_CTX][ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX];
    QTimer *isoTimer;
    unsigned char currentWriteBuffer = 0;
    unsigned long timerCount = 0;
    //Generic Functions
    unsigned char usbInit(unsigned long VIDin, unsigned long PIDin);
    unsigned char usbIsoInit(void);
public slots:
    void isoTimerTick(void);
};

#endif // GAHNOOSLASHLINUXUSBDRIVER_H
