#include "usbcallhandler.h"
#include <stdio.h>

usbCallHandler::usbCallHandler(unsigned short VID_in, unsigned short PID_in)
{
    VID = VID_in;
    PID = PID_in;
}


int usbCallHandler::setup_usb_control(){
    printf("usbCallHandler::setup_usb_control()\n");

    if(ctx != NULL){
        printf("There is already a libusb context!\n");
        return 1;
    } else printf("libusb context is null\n");

    //Initialise the Library
    int error;
    error = libusb_init(&ctx);
    if(error){
        printf("libusb_init FAILED\n");
        return -1;
    } else printf("Libusb context initialised\n");
    libusb_set_debug(ctx, 3);

    //Get a handle on the Labrador device
    handle = libusb_open_device_with_vid_pid(ctx, VID, PID);
    if(handle==NULL){
        printf("DEVICE NOT FOUND\n");
        libusb_exit(ctx);
        ctx = NULL;
        return -2;
    }
    printf("Device found!!\n");

    //Claim the interface
    error = libusb_claim_interface(handle, 0);
    if(error){
        printf("libusb_claim_interface FAILED\n");
        libusb_close(handle);
        handle = NULL;
        return -3;
    } else printf("Interface claimed!\n");

    connected = true;
    return 0;
}

int usbCallHandler::setup_usb_iso(){
    return 0;
}

int usbCallHandler::send_control_transfer(uint8_t RequestType, uint8_t Request, uint16_t Value, uint16_t Index, uint16_t Length, unsigned char *LDATA){
    unsigned char *controlBuffer;

    if(!connected){
        printf("Control packet requested before device has connected!\n");
        return -1;
    }

    if (LDATA==NULL){
        controlBuffer = inBuffer;
    }
    else controlBuffer = LDATA;

    int error = libusb_control_transfer(handle, RequestType, Request, Value, Index, controlBuffer, Length, 4000);
    if(error<0){
        printf("unixUsbDriver::usbSendControl FAILED with error %s", libusb_error_name(error));
        return error - 100;
    }
    /*
    if((error == LIBUSB_ERROR_NO_DEVICE) && (Request!=0xa7)){ //Bootloader Jump won't return; this is expected behaviour.
        printf("Device not found.  Becoming an hero.");
        connectedStatus(false);
        killMe();
    }
    */
    return 0;
}


int usbCallHandler::avrDebug(void){
    int error;
    error = send_control_transfer(0xc0, 0xa0, 0, 0, sizeof(unified_debug), NULL);

    if (error < 0){
        return error;
    }

    printf("unified debug is of size %d\n", sizeof(unified_debug));

    unified_debug *udsPtr = (unified_debug *) inBuffer;
    uint16_t trfcnt0 = (udsPtr->trfcntH0 << 8) + udsPtr->trfcntL0;
    uint16_t trfcnt1 = (udsPtr->trfcntH1 << 8) + udsPtr->trfcntL1;
    uint16_t medianTrfcnt = (udsPtr->medianTrfcntH << 8) + udsPtr->medianTrfcntL;
    uint16_t outOfRange = (udsPtr->outOfRangeH << 8) + udsPtr->outOfRangeL;
    uint16_t counter = (udsPtr->counterH << 8) + udsPtr->counterL;
    uint16_t dma_ch0_cnt = (udsPtr->dma_ch0_cntH << 8) + udsPtr->dma_ch0_cntL;
    uint16_t dma_ch1_cnt = (udsPtr->dma_ch1_cntH << 8) + udsPtr->dma_ch1_cntL;

    printf("%s", udsPtr->header);
    printf("trfcnt0 = %d\n", trfcnt0);
    printf("trfcnt1 = %d\n", trfcnt1);
    printf("medianTrfcnt = %d\n", medianTrfcnt);
    printf("outOfRange = %d\n", outOfRange);
    printf("counter = %d\n", counter);
    printf("calValNeg = %d\n", udsPtr->calValNeg);
    printf("calValPos = %d\n", udsPtr->calValPos);
    printf("CALA = %d\n", udsPtr->CALA);
    printf("CALB = %d\n", udsPtr->CALB);
    printf("dma_ch0_cnt = %d\n", dma_ch0_cnt);
    printf("dma_ch1_cnt = %d\n", dma_ch1_cnt);

    return 0;
}
