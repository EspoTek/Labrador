#ifndef WINUSBDRIVER_H
#define WINUSBDRIVER_H

//Note that big parts of this were adapted from the LibusbK example code by Travis Robinson and Xiaofan Chen.
//Actually, I'm not sure how much input Xiaofan had on the example code, but he maintains LibusbK now and deserves a lot of credit for that!
//Thanks guys!

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QTimer>

#include "functiongencontrol.h"
#include "xmega.h"
#include "desktop_settings.h"
#include "buffercontrol.h"

//libusbK includes
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "libusbk.h"

#define ISO_PACKET_SIZE 1023
#define ISO_PACKETS_PER_CTX 18
#define NUM_FUTURE_CTX 4
#define MAX_OVERLAP NUM_FUTURE_CTX+1

class winUsbDriver : public QLabel
{
    Q_OBJECT
public:
        //Generic vars
    int deviceMode = INIT_DEVICE_MODE;
    double scopeGain = 0.5;
    int dutyTemp = 0;
        //Generic Functions
    explicit winUsbDriver(QWidget *parent = 0);
    char *isoRead();
    ~winUsbDriver();
    void setBufferPtr(bufferControl *newPtr);
private:
        //Libusbk
    //GENERIC
    KUSB_HANDLE handle = NULL;
    unsigned char pipeID = 0x83;
    DWORD ec = ERROR_SUCCESS;
    //INIT
    KLST_DEVINFO_HANDLE deviceInfo = NULL;
    WINUSB_PIPE_INFORMATION pipeInfo;
    UINT deviceCount = 0;
    UCHAR pipeIndex = 0;
    KLST_HANDLE deviceList = NULL;
    //ISO
    PKISO_CONTEXT isoCtx[NUM_FUTURE_CTX];
    KOVL_HANDLE ovlkHandle[NUM_FUTURE_CTX];
    KOVL_POOL_HANDLE ovlPool;
    unsigned char dataBuffer[NUM_FUTURE_CTX][ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX];
        //Labrador Board state data (mostly)
    unsigned char fGenTriple=0;
    unsigned short gainMask = 2056;
    int fGenChannel;
    int dutyPsu = 0;
    double currentPsuVoltage;
    int digitalPinState = 0;
        //Generic vars
    functionGenControl *fGenPtr_CH1 = NULL, *fGenPtr_CH2 = NULL;
    bufferControl *bufferPtr = NULL;
    QTimer *psuTimer;
        //Generic Functions
    unsigned char usbInit(ULONG VIDin, ULONG PIDin);
    void usbSendControl(int RequestType, int Request, int Value, int Index, int Length, unsigned char *LDATA);
    void xmegaBreak(void);
    unsigned char usbIsoInit(void);
signals:
    void sendClearBuffer(bool ch3751, bool ch3752, bool ch750);
    void setVisible_CH2(bool visible);
    void gainBuffers(double multiplier);
    void disableWindow(bool enabled);
    void enableMMTimer();
    void checkXY(bool);
public slots:
    void setPsu(double voltage);
    void setFunctionGen(int channel, functionGenControl *fGenControl);
    void setDeviceMode(int mode);
    void newDig(int digState);
    void psuTick(void);
    void setGain(double newGain);
    void avrDebug(void);
};

#endif // WINUSBDRIVER_H
