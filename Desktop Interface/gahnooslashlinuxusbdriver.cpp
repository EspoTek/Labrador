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
        QThread::msleep(32);
        error = usbInit(0x03eb, 0xa000);
    }
}

gahnooSlashLinuxUsbDriver::~gahnooSlashLinuxUsbDriver(void){
    qDebug() << "\n\ngahnooSlashLinuxUsbDriver destructor ran!";
    libusb_exit(ctx);
}

unsigned char gahnooSlashLinuxUsbDriver::usbInit(unsigned long VIDin, unsigned long PIDin){
    qDebug() << "Entering gahnooSlashLinuxUsbDriver::usbInit";

    int error = libusb_init(&ctx);

    if(error){
        qDebug() << "libusb_init FAILED";
        return error;
    }
    libusb_set_debug(ctx, 3);

    handle = libusb_open_device_with_vid_pid(ctx, VIDin, PIDin);
    if(handle==NULL){
        qDebug() << "DEVICE NOT FOUND";
        return -1;
    }
    qDebug() << "Device found!!";
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
        libusb_fill_iso_transfer(isoCtx[n], handle, pipeID, dataBuffer[n], ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX, ISO_PACKETS_PER_CTX, NULL, NULL, 0);
        error = libusb_submit_transfer(isoCtx[n]);
        if(error){
            qDebug() << "libusb_submit_transfer FAILED";
            qDebug() << "ERROR" << libusb_error_name(error);
        }
    }
    isoTimer = new QTimer();
    isoTimer->setTimerType(Qt::PreciseTimer);
    isoTimer->start(ISO_TIMER_PERIOD);
    connect(isoTimer, SIGNAL(timeout()), this, SLOT(isoTimerTick()));

    qDebug() << "Setup successful!";

    return 1;
}

void gahnooSlashLinuxUsbDriver::isoTimerTick(void){
   return;
}

char *gahnooSlashLinuxUsbDriver::isoRead(unsigned int *newLength){
    *(newLength) = 0;
    return (char*) NULL;
}
