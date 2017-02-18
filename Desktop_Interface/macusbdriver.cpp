#include "macUsbDriver.h"

QMutex tcBlockMutex;

macUsbDriver::macUsbDriver(QWidget *parent) : genericUsbDriver(parent)
{
    unsigned char error = 1;
    while(error){
        error = usbInit(0x03eb, 0xa000);
        if(error)QThread::msleep(64);
    }
    setDeviceMode(deviceMode);
    newDig(digitalPinState);
    usbIsoInit();

    psuTimer = new QTimer();
    psuTimer->setTimerType(Qt::PreciseTimer);
    psuTimer->start(PSU_PERIOD);

    recoveryTimer = new QTimer();
    recoveryTimer->setTimerType(Qt::PreciseTimer);
    recoveryTimer->start(RECOVERY_PERIOD);
    connect(recoveryTimer, SIGNAL(timeout()), this, SLOT(recoveryTick()));
}

macUsbDriver::~macUsbDriver(void){
    qDebug() << "\n\nmacUsbDriver destructor ran!";
    workerThread->quit();
    workerThread->deleteLater();
    delete(isoHandler);
    delete(psuTimer);
    delete(recoveryTimer);
    delete(isoTimer);
    libusb_release_interface(handle, 0);
    libusb_exit(ctx);
}

unsigned char macUsbDriver::usbInit(unsigned long VIDin, unsigned long PIDin){
    qDebug() << "Entering macUsbDriver::usbInit";

    int error = libusb_init(&ctx);
    if(error){
        qDebug() << "libusb_init FAILED";
        return error;
    } else qDebug() << "Libusb context initialised";

    libusb_set_debug(ctx, 3);

    handle = libusb_open_device_with_vid_pid(ctx, VIDin, PIDin);
    if(handle==NULL){
        qDebug() << "DEVICE NOT FOUND";
        return -1;
    }
    qDebug() << "Device found!!";

    qDebug() << (libusb_kernel_driver_active(handle, 0) ? "KERNEL DRIVER ACTIVE" : "KERNEL DRIVER INACTIVE");
    if(libusb_kernel_driver_active(handle, 0)){
        libusb_detach_kernel_driver(handle, 0);
    }
    error = libusb_claim_interface(handle, 0);
    if(error){
        qDebug() << "libusb_claim_interface FAILED";
        qDebug() << "ERROR" << error << libusb_error_name(error);
        return error;
    } else qDebug() << "Interface claimed!";

    return 0;
}

void macUsbDriver::usbSendControl(uint8_t RequestType, uint8_t Request, uint16_t Value, uint16_t Index, uint16_t Length, unsigned char *LDATA){
    qDebug("Sending Control packet! 0x%x,\t0x%x,\t%u,\t%u,\t%d,\t%u", RequestType, Request, Value, Index, LDATA, Length);
    int error = libusb_control_transfer(handle, RequestType, Request, Value, Index, LDATA, Length, 4000);
    if(error){
        qDebug("macUsbDriver::usbSendControl FAILED with error %s", libusb_error_name(error));
    } else qDebug() << "macUsbDriver::usbSendControl SUCCESS";
    if(error == LIBUSB_ERROR_NO_DEVICE){
        qDebug() << "Device not found.  Becoming an hero.";
        killMe();
    }
    return;
}

unsigned char macUsbDriver::usbIsoInit(void){
    int error;

    for(int n=0;n<NUM_FUTURE_CTX;n++){
        isoCtx[n] = libusb_alloc_transfer(ISO_PACKETS_PER_CTX);
        transferCompleted[n].number = n;
        transferCompleted[n].completed = false;
        libusb_fill_iso_transfer(isoCtx[n], handle, pipeID, dataBuffer[n], ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX, ISO_PACKETS_PER_CTX, isoCallback, (void*)&transferCompleted[n], 4000);
        libusb_set_iso_packet_lengths(isoCtx[n], ISO_PACKET_SIZE);
        error = libusb_submit_transfer(isoCtx[n]);
        if(error){
            qDebug() << "libusb_submit_transfer FAILED";
            qDebug() << "ERROR" << libusb_error_name(error);
        } else qDebug() << "isoCtx submitted successfully!";
    }
    isoTimer = new QTimer();
    isoTimer->setTimerType(Qt::PreciseTimer);
    isoTimer->start(ISO_TIMER_PERIOD);
    connect(isoTimer, SIGNAL(timeout()), this, SLOT(isoTimerTick()));

    qDebug() << "Setup successful!";

    isoHandler = new worker();
    workerThread = new QThread();

    isoHandler->ctx = ctx;
    isoHandler->moveToThread(workerThread);
    connect(workerThread, SIGNAL(started()), isoHandler, SLOT(handle()));

    workerThread->start();

    qDebug() << "MAIN THREAD ID" << QThread::currentThreadId();
    //QThread::sleep(1);
    qDebug() << "Iso Stack initialised!";
    return 1;
}

void macUsbDriver::isoTimerTick(void){
    timerCount++;

    char subString[3] = "th";
    if(timerCount%10 == 1) strcpy(subString, "st");
    if(timerCount%10 == 2) strcpy(subString, "nd");
    if(timerCount%10 == 3) strcpy(subString, "rd");
    if((timerCount<20) && (timerCount > 10)) strcpy(subString, "th");

    //qDebug("\n\nThis is the %d%s Tick!", timerCount, subString);

    int n, error, earliest = MAX_OVERLAP;
    qint64 minFrame = 9223372036854775807; //max value for 64 bit signed

    unsigned int i, packetLength = 0;
    unsigned char* packetPointer;

    tcBlockMutex.lock();
    for (n=0; n<NUM_FUTURE_CTX; n++){
        if(transferCompleted[n].completed){
            //qDebug("Transfer %d is complete!!", n);
            if(transferCompleted[n].timeReceived < minFrame){
                minFrame = transferCompleted[n].timeReceived;
                earliest = n;
            }
        }
    }
    if (earliest == MAX_OVERLAP){
        qDebug() << "Returning at (earliest == MAX_OVERLAP)";
        tcBlockMutex.unlock();
        return;
    }

    //Copy iso data into buffer
    for(i=0;i<isoCtx[earliest]->num_iso_packets;i++){
        packetPointer = libusb_get_iso_packet_buffer_simple(isoCtx[earliest], i);
        //qDebug() << packetLength;
        memcpy(&(outBuffers[currentWriteBuffer][packetLength]), packetPointer, isoCtx[earliest]->iso_packet_desc[i].actual_length);
        packetLength += isoCtx[earliest]->iso_packet_desc[i].actual_length;
    }

    //Control data for isoDriver
    bufferLengths[currentWriteBuffer] = packetLength;
    currentWriteBuffer = !currentWriteBuffer;

    //Setup next transfer
    transferCompleted[earliest].completed = false;
    error = libusb_submit_transfer(isoCtx[earliest]);
    if(error){
        qDebug() << "libusb_submit_transfer FAILED";
        qDebug() << "ERROR" << libusb_error_name(error);
    } //else qDebug() << "isoCtx submitted successfully!";
    tcBlockMutex.unlock();
    qDebug() << "Returning at Uptick()";
    upTick();
   return;
}

char *macUsbDriver::isoRead(unsigned int *newLength){
    //*(newLength) = 0;
    //return (char*) NULL;
    qDebug() << "macUsbDriver::isoRead";
    *(newLength) = bufferLengths[!currentWriteBuffer];
    return (char*) outBuffers[(unsigned char) !currentWriteBuffer];
}

void macUsbDriver::recoveryTick(void){
    //avrDebug();
}

static void LIBUSB_CALL isoCallback(struct libusb_transfer * transfer){
    tcBlockMutex.lock();
    //int number = ((tcBlock *)transfer->user_data)->number;
    //bool completed = ((tcBlock *)transfer->user_data)->completed;

    //qDebug() << "CALLBACK";
    //qDebug() << completed;

    ((tcBlock *)transfer->user_data)->completed = true;
    ((tcBlock *)transfer->user_data)->timeReceived = QDateTime::currentMSecsSinceEpoch();
    //qDebug() << ((tcBlock *)transfer->user_data)->timeReceived;
    tcBlockMutex.unlock();
    return;
}
