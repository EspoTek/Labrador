#include "gahnooslashlinuxusbdriver.h"

gahnooSlashLinuxUsbDriver::gahnooSlashLinuxUsbDriver(QWidget *parent) : genericUsbDriver(parent)
{
    qDebug() << "Making USB Driver invisible!!";
    this->hide();

    outBuffers[0] = (unsigned char *) calloc(ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX + 8, 1);
    outBuffers[1] = (unsigned char *) calloc(ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX + 8, 1);

    bufferLengths[0] = 0;
    bufferLengths[1] = 0;

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
    connect(psuTimer, SIGNAL(timeout()), this, SLOT(psuTick()));
}

gahnooSlashLinuxUsbDriver::~gahnooSlashLinuxUsbDriver(void){
    qDebug() << "\n\ngahnooSlashLinuxUsbDriver destructor ran!";
    workerThread->quit();
    workerThread->wait();
    libusb_release_interface(handle, 0);
    libusb_exit(ctx);
}

unsigned char gahnooSlashLinuxUsbDriver::usbInit(unsigned long VIDin, unsigned long PIDin){
    qDebug() << "Entering gahnooSlashLinuxUsbDriver::usbInit";

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

void gahnooSlashLinuxUsbDriver::usbSendControl(uint8_t RequestType, uint8_t Request, uint16_t Value, uint16_t Index, uint16_t Length, unsigned char *LDATA){
    qDebug("Sending Control packet! 0x%x,\t0x%x,\t%u,\t%u,\t%d,\t%u", RequestType, Request, Value, Index, LDATA, Length);
    int error = libusb_control_transfer(handle, RequestType, Request, Value, Index, LDATA, Length, 4000);
    if(error){
        qDebug("gahnooSlashLinuxUsbDriver::usbSendControl FAILED with error %s", libusb_error_name(error));
    } else qDebug() << "gahnooSlashLinuxUsbDriver::usbSendControl SUCCESS";
    return;
}

unsigned char gahnooSlashLinuxUsbDriver::usbIsoInit(void){
    int error;

    for(int n=0;n<NUM_FUTURE_CTX;n++){
        isoCtx[n] = libusb_alloc_transfer(ISO_PACKETS_PER_CTX);
        libusb_fill_iso_transfer(isoCtx[n], handle, pipeID, dataBuffer[n], ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX, ISO_PACKETS_PER_CTX, isoCallback, (void*)n, 4000);
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
    //workerThread->start();

    return 1;
}

void gahnooSlashLinuxUsbDriver::isoTimerTick(void){
    timerCount++;

    char subString[3] = "th";
    if(timerCount%10 == 1) strcpy(subString, "st");
    if(timerCount%10 == 2) strcpy(subString, "nd");
    if(timerCount%10 == 3) strcpy(subString, "rd");
    if((timerCount<20) && (timerCount > 10)) strcpy(subString, "th");

    //qDebug("\n\nThis is the %d%s Tick!", timerCount, subString);
    return;

    int n;
    for (n=0; n<NUM_FUTURE_CTX; n++){
        if(isoCtx[n]->status==LIBUSB_TRANSFER_COMPLETED){
            qDebug("Transfer %d is complete!!", n);
        }
    }
   return;
}

char *gahnooSlashLinuxUsbDriver::isoRead(unsigned int *newLength){
    *(newLength) = 0;
    return (char*) NULL;
}

static void LIBUSB_CALL isoCallback(struct libusb_transfer * transfer){
    qDebug() << "CALLBACK" << (long) transfer->user_data;
    return;
}
