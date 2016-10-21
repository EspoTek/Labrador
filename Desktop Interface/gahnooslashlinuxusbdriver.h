#ifndef GAHNOOSLASHLINUXUSBDRIVER_H
#define GAHNOOSLASHLINUXUSBDRIVER_H

#include <QWidget>
#include <QThread>

#include "genericusbdriver.h"
#include "libusb.h"

/*while(1){
    if(libusb_event_handling_ok(ctx)){
        libusb_handle_events(ctx);
        qDebug() << "HANDLED";
    }
}*/


class worker : public QObject
{
    Q_OBJECT

public:
    worker(){};
    ~worker(){};
    libusb_context *ctx;
public slots:
    void handle(){
        while(1);
    }
};

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
    libusb_device_handle *handle = NULL;
    unsigned char pipeID = 0x83;
    //USBIso Vars
    libusb_transfer *isoCtx[NUM_FUTURE_CTX];
    unsigned char dataBuffer[NUM_FUTURE_CTX][ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX];
    QTimer *isoTimer;
    unsigned char currentWriteBuffer = 0;
    unsigned long timerCount = 0;
    worker *isoHandler;
    QThread *workerThread;
    //Generic Functions
    unsigned char usbInit(unsigned long VIDin, unsigned long PIDin);
    unsigned char usbIsoInit(void);
signals:
public slots:
    void isoTimerTick(void);
};

static void LIBUSB_CALL isoCallback(struct libusb_transfer *transfer);

#endif // GAHNOOSLASHLINUXUSBDRIVER_H
