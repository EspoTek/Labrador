#ifndef WINUSBDRIVER_H
#define WINUSBDRIVER_H

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
#define ISO_PACKETS_PER_CTX 17
#define NUM_FUTURE_CTX 56
#define MAX_OVERLAP NUM_FUTURE_CTX+1
#define ISO_TIMER_PERIOD 16
#define MAX_VALID_INDEX 374

class winUsbDriver : public QLabel
{
    Q_OBJECT
public:
    //State Vars
    int deviceMode = INIT_DEVICE_MODE;
    double scopeGain = 0.5;
    int dutyTemp = 0;
    //Generic Vars
    unsigned char *outBuffers[2];
    unsigned int bufferLengths[2];
    //Generic Functions
    explicit winUsbDriver(QWidget *parent = 0);
    char *isoRead(unsigned int *newLength);
    ~winUsbDriver();
    void setBufferPtr(bufferControl *newPtr);
    void saveState(int *_out_deviceMode, double *_out_scopeGain, double *_out_currentPsuVoltage, int *_out_digitalPinState);
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
    //State Vars
    unsigned char fGenTriple=0;
    unsigned short gainMask = 2056;
    functionGenControl *fGenPtr_CH1 = NULL, *fGenPtr_CH2 = NULL;
    int dutyPsu = 0;
    double currentPsuVoltage;
    int digitalPinState = 0;
    //Generic Vars
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
    void upTick(void);
    void killMe(void);
public slots:
    void setPsu(double voltage);
    void setFunctionGen(int channel, functionGenControl *fGenControl);
    void setDeviceMode(int mode);
    void newDig(int digState);
    void psuTick(void);
    void setGain(double newGain);
    void avrDebug(void);
    void isoTimerTick(void);
};

#endif // WINUSBDRIVER_H
