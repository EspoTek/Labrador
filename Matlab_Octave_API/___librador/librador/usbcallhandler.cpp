#include "usbcallhandler.h"
#include <stdio.h>

#include "o1buffer.h"
#include <mutex>
#include <chrono>
#include <thread>

std::mutex usb_shutdown_mutex;
bool usb_shutdown_requested = false;
int usb_shutdown_remaining_transfers = NUM_FUTURE_CTX;
bool thread_active = true;

int begin_usb_thread_shutdown(){
    usb_shutdown_mutex.lock();
    usb_shutdown_requested = true;
    usb_shutdown_mutex.unlock();
    return 0;
}

bool usb_iso_needs_rearming(){
    bool tempReturn;
    usb_shutdown_mutex.lock();
    tempReturn = !usb_shutdown_requested;
    usb_shutdown_mutex.unlock();
    return tempReturn;
}

int decrement_remaining_transfers(){
    usb_shutdown_mutex.lock();
    usb_shutdown_remaining_transfers--;
    usb_shutdown_mutex.unlock();
    return 0;
}

bool safe_to_exit_thread(){
    bool tempReturn;
    usb_shutdown_mutex.lock();
    tempReturn = (usb_shutdown_remaining_transfers == 0);
    usb_shutdown_mutex.unlock();
    return tempReturn;
}

//shared vars
o1buffer *internal_o1_buffer;

static void LIBUSB_CALL isoCallback(struct libusb_transfer * transfer){

    //Thread mutex??
    printf("Copy the data...\n");
    for(int i=0;i<transfer->num_iso_packets;i++){
        unsigned char *packetPointer = libusb_get_iso_packet_buffer_simple(transfer, i);
        if(transfer->actual_length){
            printf("Expected length is %d\n", transfer->length);
            printf("Actual length is %d\n", transfer->actual_length);
            printf("\n");
        }
        //TODO: a switch statement here to handle all the modes.
        internal_o1_buffer->addVector(packetPointer, 375);
    }
    printf("Re-arm the endpoint...\n");
    if(usb_iso_needs_rearming()){
        int error = libusb_submit_transfer(transfer);
        if(error){
            printf("Error re-arming the endpoint!\n");
            begin_usb_thread_shutdown();
            decrement_remaining_transfers();
            printf("Transfer not being rearmed!  %d armed transfers remaining\n", usb_shutdown_remaining_transfers);
        }
    } else {
        decrement_remaining_transfers();
        printf("Transfer not being rearmed!  %d armed transfers remaining\n", usb_shutdown_remaining_transfers);
    }
    return;
}

void usb_polling_function(libusb_context *ctx){
    printf("usb_polling_function thread spawned\n");
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;//ISO_PACKETS_PER_CTX*4000;
    while(!safe_to_exit_thread()){
        printf("usb_polling_function begin loop\n");
        if(libusb_event_handling_ok(ctx)){
            libusb_handle_events_timeout(ctx, &tv);
        }
    }
}

usbCallHandler::usbCallHandler(unsigned short VID_in, unsigned short PID_in)
{
    VID = VID_in;
    PID = PID_in;

    for(int k=0; k<NUM_ISO_ENDPOINTS; k++){
        pipeID[k] = 0x81+k;
        printf("pipeID %d = %d\n", k, pipeID[k]);
    }

    internal_o1_buffer = new o1buffer();

    //In case it was deleted before; reset the shared variables.
    usb_shutdown_requested = false;
    usb_shutdown_remaining_transfers = NUM_FUTURE_CTX;
    thread_active = true;
}

usbCallHandler::~usbCallHandler(){
    //Kill off usb_polling_thread.  Maybe join then get it to detect its own timeout condition.
    printf("Calling destructor for librador USB call handler\n");
    begin_usb_thread_shutdown();

    printf("Shutting down USB polling thread...\n");
    usb_polling_thread->join();
    printf("USB polling thread stopped.\n");
    delete usb_polling_thread;

    for (int i=0; i<NUM_FUTURE_CTX; i++){
        for (int k=0; k<NUM_ISO_ENDPOINTS; k++){
            libusb_free_transfer(isoCtx[k][i]);
        }
    }
    printf("Transfers freed.\n");

    if(handle != NULL){
    libusb_release_interface(handle, 0);
        printf("Interface released\n");
        libusb_close(handle);
        printf("Device Closed\n");
    }
    if(ctx != NULL){
        libusb_exit(ctx);
        printf("Libusb exited\n");
    }

    printf("librador USB call handler deleted\n");
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
/*
    error = libusb_set_interface_alt_setting(handle, 0, 0);
    if(error){
        printf("libusb_set_interface_alt_setting FAILED\n");
        libusb_close(handle);
        handle = NULL;
        return -4;
    } else printf("bAlternateSetting claimed!\n");
*/
    connected = true;

    #warning Hack here...
    #warning Hack here...
    #warning Hack here...
    #warning Hack here...
    #warning Hack here...
    #warning Hack here...
    #warning Hack here...
    #warning Hack here...
    #warning Hack here...
    #warning Hack here...
    #warning Hack here...
    #warning Hack here...
    #warning Hack here...
    #warning Hack here...
    #warning Hack here...
    #warning Hack here...
    #warning Hack here...

    send_control_transfer(0x40, 0xa5, 0x0000, 0x0808, 0, NULL);
    send_control_transfer(0x40, 0xa6, 0x0000, 0x0000, 0, NULL);

    return 0;
}

int usbCallHandler::setup_usb_iso(){
    int error;
    printf("usbCallHandler::setup_usb_iso()\n");

    for(int n=0;n<NUM_FUTURE_CTX;n++){
        for (unsigned char k=0;k<NUM_ISO_ENDPOINTS;k++){
            isoCtx[k][n] = libusb_alloc_transfer(ISO_PACKETS_PER_CTX);
            libusb_fill_iso_transfer(isoCtx[k][n], handle, pipeID[k], dataBuffer[k][n], ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX, ISO_PACKETS_PER_CTX, isoCallback, NULL, 4000);
            libusb_set_iso_packet_lengths(isoCtx[k][n], ISO_PACKET_SIZE);
            error = libusb_submit_transfer(isoCtx[k][n]);
            if(error){
                printf("libusb_submit_transfer #%d:%d FAILED with error %d %s\n", n, k, error, libusb_error_name(error));
                return error;
            }
        }
    }

    usb_polling_thread = new std::thread(usb_polling_function, ctx);
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

std::vector<double>* usbCallHandler::getMany_double(int numToGet, int interval_samples, int delay_sample, int filter_mode){
    return internal_o1_buffer->getMany_double(numToGet, interval_samples, delay_sample, filter_mode);
}

int usbCallHandler::send_device_reset(){
    libusb_reset_device(handle);
}
