// Copyright (C) 2017, 2018, 2019, 2020, 2021 Christopher Paul Esposito
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef unixUsbDriver_H
#define unixUsbDriver_H

#include <QWidget>
#include <QThread>
#include <QMutex>
#include <QDateTime>

#include "genericusbdriver.h"
#include "libusb.h"
extern "C"
{
    #include "libdfuprog.h"
}

#define MAX_ALLOWABLE_CUMULATIVE_FRAME_ERROR 50

//tcBlock is fed to the callback in the libusb user data section.
typedef struct tcBlock{
    int number;
    bool completed;
    qint64 timeReceived;
} tcBlock;

//Oddly, libusb requires you to make a blocking libusb_handle_events() call in order to execute the callbacks for an asynchronous transfer.
//Since the call is blocking, this worker must exist in a separate, low priority thread!
class worker : public QObject
{
    Q_OBJECT

public:
    worker(){};
    ~worker(){};
    libusb_context *ctx;
    bool stopTime = false;
    unsigned char cleanupRemaining = 4;
public slots:
    void handle(){
        qDebug() << "SUB THREAD ID" << QThread::currentThreadId();
        while(cleanupRemaining){
            //qDebug() << cleanupRemaining;
            if(libusb_event_handling_ok(ctx)){
                libusb_handle_events_timeout(ctx, &tv);
                //qDebug() << "HANDLED";
            }
            if(stopTime){
                if(cleanupRemaining){
                    cleanupRemaining--;
                    qDebug("Cleaning... #%hhu phases remain.\n", cleanupRemaining);
                }
            }
        }
        qDebug() << "Cleanup complete";  //THIS THREAD STILL EXISTS
    }
};

//This is the actual unixUsbDriver
//It handles the Mac/Linux specific parts of USB communication, through libusb.
//See genericUsbDriver for the non-platform-specific parts.
class unixUsbDriver : public genericUsbDriver
{
    Q_OBJECT
public:
    explicit unixUsbDriver(QWidget *parent = 0);
    ~unixUsbDriver();
    void usbSendControl(uint8_t RequestType, uint8_t Request, uint16_t Value, uint16_t Index, uint16_t Length, unsigned char *LDATA);
    char *isoRead(unsigned int *newLength);
    void manualFirmwareRecovery(void);
protected:
    //USB Vars
    libusb_context *ctx = NULL;
    libusb_device_handle *handle = NULL;
    //USBIso Vars
    unsigned char *midBuffer_current[NUM_ISO_ENDPOINTS];
    unsigned char *midBuffer_prev[NUM_ISO_ENDPOINTS];
    qint64 midBufferOffsets[NUM_ISO_ENDPOINTS];
    libusb_transfer *isoCtx[NUM_ISO_ENDPOINTS][NUM_FUTURE_CTX] = { };
    tcBlock transferCompleted[NUM_ISO_ENDPOINTS][NUM_FUTURE_CTX];
    unsigned char dataBuffer[NUM_ISO_ENDPOINTS][NUM_FUTURE_CTX][ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX];
    worker *isoHandler = nullptr;
    QThread *workerThread = nullptr;
    int cumulativeFramePhaseErrors = 0;
    //Generic Functions
    virtual unsigned char usbInit(unsigned long VIDin, unsigned long PIDin);
    int usbIsoInit(void);
    virtual int flashFirmware(void);
    bool allEndpointsComplete(int n);
    bool shutdownMode = false;
    int numCancelled = 0;
signals:
public slots:
    void isoTimerTick(void);
    void recoveryTick(void);
    void shutdownProcedure(void);
    void backupCleanup(void);
};

//Callback on iso transfer complete.
static void LIBUSB_CALL isoCallback(struct libusb_transfer * transfer){
    tcBlockMutex.lock();
    //int number = ((tcBlock *)transfer->user_data)->number;
    //bool completed = ((tcBlock *)transfer->user_data)->completed;

    //qDebug() << "CALLBACK" << number;
    //qDebug() << completed;

    if(transfer->status!=LIBUSB_TRANSFER_CANCELLED){
        ((tcBlock *)transfer->user_data)->completed = true;
        ((tcBlock *)transfer->user_data)->timeReceived = QDateTime::currentMSecsSinceEpoch();
    }
    //qDebug() << ((tcBlock *)transfer->user_data)->timeReceived;
    tcBlockMutex.unlock();
    return;
}

#endif // unixUsbDriver_H
