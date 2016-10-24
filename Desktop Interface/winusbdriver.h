#ifndef WINUSBDRIVER_H
#define WINUSBDRIVER_H

//libusbK includes
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "libusbk.h"

#include "genericusbdriver.h"

class winUsbDriver : public genericUsbDriver
{
    Q_OBJECT
public:
    //Generic Functions
    explicit winUsbDriver(QWidget *parent = 0);
    ~winUsbDriver();
    void usbSendControl(uint8_t RequestType, uint8_t Request, uint16_t Value, uint16_t Index, uint16_t Length, unsigned char *LDATA);
    char *isoRead(unsigned int *newLength);
private:
    //USB Vars
    KUSB_HANDLE handle = NULL;
    //USBIso Vars
    PKISO_CONTEXT isoCtx[NUM_FUTURE_CTX];
    KOVL_HANDLE ovlkHandle[NUM_FUTURE_CTX];
    KOVL_POOL_HANDLE ovlPool;
    unsigned char dataBuffer[NUM_FUTURE_CTX][ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX];
    //Generic Functions
    unsigned char usbInit(unsigned long VIDin, unsigned long PIDin);
    unsigned char usbIsoInit(void);
signals:
public slots:
};

#endif // WINUSBDRIVER_H
