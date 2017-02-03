#ifndef GENERICUSBDRIVER_H
#define GENERICUSBDRIVER_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <math.h>
#include <stdint.h>

#include "functiongencontrol.h"
#include "xmega.h"
#include "desktop_settings.h"
#include "buffercontrol.h"
#include "unified_debug_structure.h"

#define ISO_PACKET_SIZE 125
#define ISO_PACKETS_PER_CTX 17
#define NUM_FUTURE_CTX 36
#define ISO_TIMER_PERIOD 16
#define NUM_ISO_ENDPOINTS 6
#define MAX_OVERLAP (NUM_FUTURE_CTX*NUM_ISO_ENDPOINTS + 1)

//genericUsbDriver handles the parts of the USB stack that are not platform-dependent.
//It exists as a superclass for winUsbDriver (on Windows) or unixUsbDriver (on Linux)

class genericUsbDriver : public QLabel
{
    Q_OBJECT
public:
    //State Vars
    int deviceMode = INIT_DEVICE_MODE;
    double scopeGain = 0.5;
    int dutyTemp = 21;
    //Generic Vars
    unsigned char *outBuffers[2];
    unsigned int bufferLengths[2];
    //Generic Functions
    explicit genericUsbDriver(QWidget *parent = 0);
    virtual char *isoRead(unsigned int *newLength) = 0;
    void setBufferPtr(bufferControl *newPtr);
    void saveState(int *_out_deviceMode, double *_out_scopeGain, double *_out_currentPsuVoltage, int *_out_digitalPinState);
    virtual void usbSendControl(uint8_t RequestType, uint8_t Request, uint16_t Value, uint16_t Index, uint16_t Length, unsigned char *LDATA) = 0;
protected:
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
    unsigned char pipeID[3];
    QTimer *isoTimer;
    unsigned char currentWriteBuffer = 0;
    unsigned long timerCount = 0;
    unsigned char inBuffer[256];
    //Generic Functions
    virtual unsigned char usbInit(unsigned long VIDin, unsigned long PIDin) = 0;
    virtual unsigned char usbIsoInit(void) = 0;
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
    virtual void isoTimerTick(void) = 0;
};


#endif // GENERICUSBDRIVER_H
