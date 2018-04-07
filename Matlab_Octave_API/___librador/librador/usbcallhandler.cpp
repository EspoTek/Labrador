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
o1buffer *internal_o1_buffer_375_CH1;
o1buffer *internal_o1_buffer_375_CH2;
o1buffer *internal_o1_buffer_750;


static void LIBUSB_CALL isoCallback(struct libusb_transfer * transfer){

    //Thread mutex??
    //printf("Copy the data...\n");
    for(int i=0;i<transfer->num_iso_packets;i++){
        unsigned char *packetPointer = libusb_get_iso_packet_buffer_simple(transfer, i);
        if(transfer->actual_length){
            //printf("Expected length is %d\n", transfer->length);
            //printf("Actual length is %d\n", transfer->actual_length);
            //printf("\n");
        }
        //TODO: a switch statement here to handle all the modes.
        internal_o1_buffer_375_CH1->addVector((char*) packetPointer, 375);
    }
    //printf("Re-arm the endpoint...\n");
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
        //printf("usb_polling_function begin loop\n");
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

    internal_o1_buffer_375_CH1 = new o1buffer();
    internal_o1_buffer_375_CH2 = new o1buffer();
    internal_o1_buffer_750 = new o1buffer();

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

    set_device_mode(0);
    set_gain(1);

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
        printf("send_control_transfer FAILED with error %s", libusb_error_name(error));
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

    printf("unified debug is of size %lu\n", sizeof(unified_debug));

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
    #warning ASSUMING MODE 0
    #warning ASSUMING MODE 0
    #warning ASSUMING MODE 0
    #warning ASSUMING MODE 0
    #warning ASSUMING MODE 0
    #warning ASSUMING MODE 0
    #warning ASSUMING MODE 0
    #warning ASSUMING MODE 0
    #warning ASSUMING MODE 0
    #warning ASSUMING MODE 0
    #warning ASSUMING MODE 0

    return internal_o1_buffer_375_CH1->getMany_double(numToGet, interval_samples, delay_sample, filter_mode);
}

int usbCallHandler::send_device_reset(){
    libusb_reset_device(handle);
    return 0;
}


int usbCallHandler::set_device_mode(int mode){
    if((mode < 0) || (mode > MAX_SUPPORTED_DEVICE_MODE)){
        return -1;
    }
    deviceMode = mode;
    send_control_transfer(0x40, 0xa5, (mode == 5 ? 0 : mode), gainMask, 0, NULL);

    send_function_gen_settings(1);
    send_function_gen_settings(2);
    return 0;
}

int usbCallHandler::set_gain(double newGain){
    //See XMEGA_AU Manual, page 359.  ADC.CTRL.GAIN.
    if(newGain==0.5) gainMask = 0x07;
    else if (newGain == 1) gainMask = 0x00;
    else if (newGain == 2) gainMask = 0x01;
    else if (newGain == 4) gainMask = 0x02;
    else if (newGain == 8) gainMask = 0x03;
    else if (newGain == 16) gainMask = 0x04;
    else if (newGain == 32) gainMask = 0x05;
    else if (newGain == 64) gainMask = 0x06;
    else{
      printf("Invalid gain value.  Valid values are 0.1, 1, 2, 4, 8, 16, 32, 64\n");
      return -1;
    }

    gainMask = gainMask << 2;
    gainMask |= (gainMask << 8);
    send_control_transfer(0x40, 0xa5, deviceMode, gainMask, 0, NULL);
    internal_o1_buffer_375_CH1->librador_scope_gain = newGain;
    internal_o1_buffer_375_CH2->librador_scope_gain = newGain;
    internal_o1_buffer_750->librador_scope_gain = newGain;
    return 0;
}

int usbCallHandler::update_function_gen_settings(int channel, unsigned char *sampleBuffer, int numSamples, double usecs_between_samples, double amplitude_v, double offset_v){


    //Parse the channel
    fGenSettings *fGenSelected;
    if(channel == 1){
        fGenSelected = &functionGen_CH1;
    } else if (channel == 2){
        fGenSelected = &functionGen_CH2;
    } else {
        return -1;  //Invalid channel
    }

    //Update number of samples.
    fGenSelected->numSamples = numSamples;

    //Does the output amplifier need to be enabled?
    if ((amplitude_v+offset_v) > FGEN_LIMIT){
        amplitude_v = amplitude_v / 3;
        offset_v = offset_v / 3;
        if(channel == 1){
            fGenTriple |= 0b00000010;  //This is correct.  Somehow the channels got switched around on the board's firmware and this is a duct-tape solution.
        } else {
            fGenTriple |= 0x00000001;
        }
    }
    else {
        if(channel == 1){
            fGenTriple &= 0b11111101;
        } else {
            fGenTriple &= 0b11111110;
        }
    }

    //Fiddle with the waveform to deal with the fact that the Xmega has a minimum DAC output value.
    double amplitude_sample = (amplitude_v * 255) / FGEN_LIMIT;
    double offset_sample = (offset_v * 255) / FGEN_LIMIT;
    if (offset_sample < FGEN_SAMPLE_MIN){  //If the offset is in the range where the XMEGA output cannot physically drive the signal that low...
        if (amplitude_sample > FGEN_SAMPLE_MIN){  //And the amplitude of the signal can go above this minimum range
            amplitude_sample -= FGEN_SAMPLE_MIN;  //Then reduce the amplitude and add a small offset
            }
        else {
            amplitude_sample = 0;
        }
        offset_sample = FGEN_SAMPLE_MIN;
    }

    //Apply amplitude and offset scaling to all samples.
    double tempDouble;
    for (int i=0;i<numSamples;i++){
        tempDouble = (double) sampleBuffer[i];
        tempDouble *= amplitude_sample;
        tempDouble /= 255.0;
        tempDouble += offset_sample;
        fGenSelected->samples[i] = (uint8_t) tempDouble;
    }

    //Calculate timer values
    int validClockDivs[7] = {1, 2, 4, 8, 64, 256, 1024};

    int clkSetting;
    for(clkSetting = 0; clkSetting<7; clkSetting++){
        if ( ((XMEGA_MAIN_FREQ * usecs_between_samples)/(1000000 * validClockDivs[clkSetting])) < 65535)
             break;
    }
    fGenSelected->timerPeriod = (usecs_between_samples * XMEGA_MAIN_FREQ) / (1000000 * validClockDivs[clkSetting]);
    fGenSelected->clockDividerSetting = clkSetting + 1;

    return 0;
}

int usbCallHandler::send_function_gen_settings(int channel){
    if(channel == 1){
        if(functionGen_CH1.numSamples == 0){
            return -1; //Channel not initialised
        }
        send_control_transfer(0x40, 0xa2, functionGen_CH1.timerPeriod, functionGen_CH1.clockDividerSetting, functionGen_CH1.numSamples, functionGen_CH1.samples);
    } else if (channel == 2){
        if(functionGen_CH2.numSamples == 0){
            return -1; //Channel not initialised
        }
        send_control_transfer(0x40, 0xa1, functionGen_CH1.timerPeriod, functionGen_CH1.clockDividerSetting, functionGen_CH1.numSamples, functionGen_CH1.samples);
    } else {
        return -2; //Invalid channel
    }
    send_control_transfer(0x40, 0xa4, fGenTriple, 0, 0, NULL);
    return 0;
}

int usbCallHandler::set_psu_voltage(double voltage){
    double vinp = voltage/11;
    double vinn = 0;

    uint8_t dutyPsu = (uint8_t) ((vinp - vinn)/vref_psu * gain_psu * PSU_ADC_TOP);


    if ((dutyPsu>106) || (dutyPsu<21)){
        return -1;  //Out of range
    }
    send_control_transfer(0x40, 0xa3, dutyPsu, 0, 0, NULL);
    return 0;
}

int usbCallHandler::set_digital_state(uint8_t digState){
    send_control_transfer(0x40, 0xa6, digState, 0, 0, NULL);
    #warning Need a macro to return on failure of send_control_transfer()
    #warning Need a macro to return on failure of send_control_transfer()
    #warning Need a macro to return on failure of send_control_transfer()
    #warning Need a macro to return on failure of send_control_transfer()
    #warning Need a macro to return on failure of send_control_transfer()
    #warning Need a macro to return on failure of send_control_transfer()
    #warning Need a macro to return on failure of send_control_transfer()
    #warning Need a macro to return on failure of send_control_transfer()
    #warning Need a macro to return on failure of send_control_transfer()
    #warning Need a macro to return on failure of send_control_transfer()
    #warning Need a macro to return on failure of send_control_transfer()
    #warning Need a macro to return on failure of send_control_transfer()
    return 0;
}

int usbCallHandler::reset_device(bool goToBootloader){
    send_control_transfer(0x40, 0xa7, (goToBootloader ? 1 : 0), 0, 0, NULL);
    return 0;
}

uint16_t usbCallHandler::get_firmware_version(){
    send_control_transfer(0xc0, 0xa8, 0, 0, 2, NULL);
    return *((uint16_t *) inBuffer);
}

uint8_t usbCallHandler::get_firmware_variant(){
    send_control_transfer(0xc0, 0xa9, 0, 0, 1, NULL);
    return *((uint8_t *) inBuffer);
}

double usbCallHandler::get_samples_per_second(){
    switch(deviceMode){
    case 0:
        return (double)(375000.0);
    case 1:
        return (double)(375000.0);
    case 2:
        return (double)(375000.0);
    case 6:
        return (double)(750000.0);
    case 7:
        return (double)(375000.0);
    default:
        return 0;
    }
}
