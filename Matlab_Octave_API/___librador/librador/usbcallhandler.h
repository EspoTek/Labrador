#ifndef USBCALLHANDLER_H
#define USBCALLHANDLER_H

#include "libusb.h"
#include <thread>
#include <vector>

#define NUM_ISO_ENDPOINTS (1)
#define NUM_FUTURE_CTX (4)
#define ISO_PACKET_SIZE (750)
#define ISO_PACKETS_PER_CTX (33)
#define MAX_SUPPORTED_DEVICE_MODE (7)
#define FGEN_LIMIT (3.2)
#define FGEN_MAX_SAMPLES (512)
#define FGEN_SAMPLE_MIN (5.0)
#define XMEGA_MAIN_FREQ (48000000)

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

typedef struct fGenSettings{
    uint8_t samples[FGEN_MAX_SAMPLES];
    int numSamples = 0;
    uint16_t timerPeriod = 0;
    uint8_t clockDividerSetting = 0;
} fGenSettings;


class usbCallHandler
{
public:
    usbCallHandler(unsigned short VID_in, unsigned short PID_in);
    ~usbCallHandler();
    int setup_usb_control();
    int setup_usb_iso();
    int send_control_transfer(uint8_t RequestType, uint8_t Request, uint16_t Value, uint16_t Index, uint16_t Length, unsigned char *LDATA);
    int avrDebug(void);
    int send_device_reset();
    std::vector<double> *getMany_double(int numToGet, int interval_samples, int delay_sample, int filter_mode);
    bool connected;
    //Control Command Vars
    uint16_t gainMask = 0x0000;
    int deviceMode = 0;
    //Control Commands
    int set_device_mode(int mode);
    int set_gain(double newGain);
    int update_function_gen_settings(int channel, unsigned char* sampleBuffer, int numSamples, double usecs_between_samples, double amplitude_v, double offset_v);
    int send_function_gen_settings(int channel);
private:
    unsigned short VID, PID;
    libusb_context *ctx = NULL;
    libusb_device_handle *handle = NULL;
    unsigned char inBuffer[256];

    //USBIso Vars
    unsigned char pipeID[NUM_ISO_ENDPOINTS];
    libusb_transfer *isoCtx[NUM_ISO_ENDPOINTS][NUM_FUTURE_CTX];
    unsigned char dataBuffer[NUM_ISO_ENDPOINTS][NUM_FUTURE_CTX][ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX];
    std::thread *usb_polling_thread;
    //Control Vars
    uint8_t fGenTriple = 0;
    fGenSettings functionGen_CH1;
    fGenSettings functionGen_CH2;
};

#endif // USBCALLHANDLER_H
