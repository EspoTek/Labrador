#ifndef USBCALLHANDLER_H
#define USBCALLHANDLER_H

#include "libusb.h"

//EVERYTHING MUST BE SENT ONE BYTE AT A TIME, HIGH AND LOW BYTES SEPARATE, IN ORDER TO AVOID ISSUES WITH ENDIANNESS.
typedef struct uds{
    volatile char header[9];
    volatile uint8_t trfcntL0;
    volatile uint8_t trfcntH0;
    volatile uint8_t trfcntL1;
    volatile uint8_t trfcntH1;
    volatile uint8_t medianTrfcntL;
    volatile uint8_t medianTrfcntH;
    volatile uint8_t calValNeg;
    volatile uint8_t calValPos;
    volatile uint8_t CALA;
    volatile uint8_t CALB;
    volatile uint8_t outOfRangeL;
    volatile uint8_t outOfRangeH;
    volatile uint8_t counterL;
    volatile uint8_t counterH;
    volatile uint8_t dma_ch0_cntL;
    volatile uint8_t dma_ch0_cntH;
    volatile uint8_t dma_ch1_cntL;
    volatile uint8_t dma_ch1_cntH;

} unified_debug;

class usbCallHandler
{
public:
    usbCallHandler(unsigned short VID_in, unsigned short PID_in);
    int setup_usb_control();
    int setup_usb_iso();
    int send_control_transfer(uint8_t RequestType, uint8_t Request, uint16_t Value, uint16_t Index, uint16_t Length, unsigned char *LDATA);
    int avrDebug(void);
    bool connected;
private:
    unsigned short VID, PID;
    libusb_context *ctx = NULL;
    libusb_device_handle *handle = NULL;
    unsigned char inBuffer[256];
};

#endif // USBCALLHANDLER_H
