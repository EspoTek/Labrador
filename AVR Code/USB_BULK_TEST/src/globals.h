/*
 * globals.h
 *
 * Created: 18/04/2015 12:44:42 PM
 *  Author: Esposch
 */ 


#ifndef GLOBALS_H_
#define GLOBALS_H_

#define VERO

#define TC_SPISLAVE TCD0
#define TC_PSU TCD1
#define TC_PSU_OVF TCD1_OVF_vect
#define TC_DAC TCC0
#define TCDAC_OVF EVSYS_CHMUX_TCC0_OVF_gc
#define TC_AUXDAC TCC1
#define TCDAC_AUX_OVF EVSYS_CHMUX_TCC1_OVF_gc
#define HALFPACKET_SIZE 375
#define PACKET_SIZE 750
#define B2_START 1125
#define BUFFER_SIZE PACKET_SIZE*2
#define DACBUF_SIZE 512

COMPILER_WORD_ALIGNED
extern volatile unsigned char isoBuf[BUFFER_SIZE];
COMPILER_WORD_ALIGNED
extern volatile unsigned char dacBuf_CH1[DACBUF_SIZE];
extern volatile unsigned char dacBuf_CH2[DACBUF_SIZE];

extern volatile unsigned char b1_state;
extern volatile unsigned char b2_state;
extern volatile unsigned char usb_state;

extern volatile bool main_b_vendor_enable;

extern volatile uint16_t dacBuf_len;
extern volatile uint16_t auxDacBufLen;

extern volatile unsigned char dummy;

extern volatile unsigned char global_mode;

extern volatile char PSU_target;

extern volatile unsigned char test_byte;

#endif /* GLOBALS_H_ */