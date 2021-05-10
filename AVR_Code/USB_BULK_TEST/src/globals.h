/*
 * globals.h
 *
 * Created: 18/04/2015 12:44:42 PM
 *  Author: Esposch
 */

/* Copyright (C) 2018 Christopher Paul Esposito

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:

   (1) Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   (2) Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in
   the documentation and/or other materials provided with the
   distribution.

   (3)The name of the author may not be used to
   endorse or promote products derived from this software without
   specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
   STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
   IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef GLOBALS_H_
#define GLOBALS_H_

//#define SINGLE_ENDPOINT_INTERFACE

//#define VERO
#define OVERCLOCK 48
#define FIRMWARE_VERSION_ID 0x0006
#define ATMEL_DFU_OFFSET 0x01fc

#define TC_SPISLAVE TCD0
#define TC_PSU TCD1
#define TC_PSU_OVF TCD1_OVF_vect
#define TC_DAC TCC0
#define TCDAC_OVF EVSYS_CHMUX_TCC0_OVF_gc
#define TC_AUXDAC TCC1
#define TC_CALI TCE0
#define TCDAC_AUX_OVF EVSYS_CHMUX_TCC1_OVF_gc
#define HALFPACKET_SIZE 375
#define PACKET_SIZE 750
#define B2_START 1125
#define BUFFER_SIZE (PACKET_SIZE*2)
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

extern volatile unsigned char debugOnNextEnd;

extern volatile unsigned int median_TRFCNT;

extern volatile unsigned short dma_ch0_ran;
extern volatile unsigned short dma_ch1_ran;

extern volatile unsigned char futureMode;
extern volatile unsigned char modeChanged;

COMPILER_WORD_ALIGNED
extern const unsigned short firmver;
extern const unsigned char variant;

#include "unified_debug_structure.h"
extern unified_debug uds;

#endif /* GLOBALS_H_ */
