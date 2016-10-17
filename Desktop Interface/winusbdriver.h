#ifndef WINUSBDRIVER_H
#define WINUSBDRIVER_H

#include "genericusbdriver.h"

class winUsbDriver : public genericUsbDriver
{
    Q_OBJECT
public:
    //Generic Functions
    explicit winUsbDriver(QWidget *parent = 0);
    ~winUsbDriver();
    void usbSendControl(int RequestType, int Request, int Value, int Index, int Length, unsigned char *LDATA);
    char *isoRead(unsigned int *newLength);
private:
    //USB Vars
    KUSB_HANDLE handle = NULL;
    unsigned char pipeID = 0x83;
    //USBIso Vars
    PKISO_CONTEXT isoCtx[NUM_FUTURE_CTX];
    KOVL_HANDLE ovlkHandle[NUM_FUTURE_CTX];
    KOVL_POOL_HANDLE ovlPool;
    unsigned char dataBuffer[NUM_FUTURE_CTX][ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX];
    QTimer *isoTimer;
    unsigned char currentWriteBuffer = 0;
    unsigned long timerCount = 0;
    //Generic Functions
    unsigned char usbInit(ULONG VIDin, ULONG PIDin);
    unsigned char usbIsoInit(void);
signals:
public slots:
    void isoTimerTick(void);
};

#endif // WINUSBDRIVER_H
