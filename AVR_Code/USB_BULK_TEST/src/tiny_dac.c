/*
 * tiny_dac.c
 *
 * Created: 3/07/2015 1:06:44 PM
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

#include "tiny_dac.h"
#include "tiny_adc.h"

#include <avr/pgmspace.h>
#include <stddef.h>

void tiny_dac_setup(void){

	//Turn on in PR
	PR.PRPB &=0b11111011;

	DACB.CTRLA = DAC_CH1EN_bm | DAC_CH0EN_bm | DAC_ENABLE_bm;
	DACB.CTRLB = DAC_CHSEL_DUAL_gc;
	DACB.CTRLC = DAC_REFSEL_AVCC_gc | DAC_LEFTADJ_bm;
	//EVCTRL unset
	//DACB.CH0DATAH = 127;//contains (8-bit) sample, assuming left adjust!

	//TODO: Calibrate
	DACB.CH0GAINCAL = ReadCalibrationByte(offsetof(NVM_PROD_SIGNATURES_t, DACB0GAINCAL));	//Load calibration bytes from production row.
	DACB.CH0OFFSETCAL = ReadCalibrationByte(offsetof(NVM_PROD_SIGNATURES_t, DACB0OFFCAL));	//Load calibration bytes from production row.

	DACB.CH1GAINCAL = ReadCalibrationByte(offsetof(NVM_PROD_SIGNATURES_t, DACB1GAINCAL));	//Load calibration bytes from production row.
	DACB.CH1OFFSETCAL = ReadCalibrationByte(offsetof(NVM_PROD_SIGNATURES_t, DACB1OFFCAL));	//Load calibration bytes from production row.

	//Set up for triple mode!
	PORTB.DIR |= 0x03;
	PORTB.OUT = 0x00;
}
