/*
 * tiny_adc.c
 *
 * Created: 19/06/2015 7:17:23 PM
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

#include "tiny_adc.h"
#include "globals.h"
#include "string.h"
#include <asf.h>
#include <stdio.h>
#include <avr/io.h>

// These 2 files need to be included in order to read
// the production calibration values from EEPROM
#include <avr/pgmspace.h>
#include <stddef.h>

void tiny_adc_setup(unsigned char ch2_enable, unsigned char seven_fiddy_ksps){
	PR.PRPA &=0b11111101;

	ADCA.CTRLA = 0x00; //Turn off
	ADCA.CTRLB = ADC_FREERUN_bm | (seven_fiddy_ksps == 2 ? ADC_RESOLUTION_LEFT12BIT_gc : ADC_RESOLUTION_8BIT_gc) | ADC_CONMODE_bm ;
	ADCA.REFCTRL = ADC_REFSEL_INTVCC2_gc;
	ADCA.EVCTRL = ch2_enable ? ADC_SWEEP_0123_gc : ADC_SWEEP_01_gc;  //Non-zero causes issues with interrupts!  ;.;

	#if OVERCLOCK == 48
		ADCA.PRESCALER = seven_fiddy_ksps == 1 ? ADC_PRESCALER_DIV32_gc : ADC_PRESCALER_DIV64_gc;  //ADC Clock = Sysclock/128
	#else
		ADCA.PRESCALER = seven_fiddy_ksps == 1 ? ADC_PRESCALER_DIV16_gc : ADC_PRESCALER_DIV32_gc;  //ADC Clock = Sysclock/128
	#endif
	ADCA.CALL = ReadCalibrationByte(offsetof(NVM_PROD_SIGNATURES_t, ADCACAL0));	//Load calibration bytes from production row.
	ADCA.CALH = ReadCalibrationByte(offsetof(NVM_PROD_SIGNATURES_t, ADCACAL1));	//Load calibration bytes from production row.
	ADCA.CMP = 0x0000;		//No compare used

	ADCA.CTRLA = ADC_ENABLE_bm;

	tiny_adc_pid_setup();

	return;
}

void tiny_adc_ch0setup(unsigned char gain_mask){
	ADCA.CH0.CTRL = 0x00; //Reset
	ADCA.CH0.CTRL = ADC_CH_START_bm | (gain_mask&0x1c) | ADC_CH_INPUTMODE_DIFFWGAIN_gc;
	#ifdef VERO
			ADCA.CH0.MUXCTRL = ADC_CH_MUXPOS_PIN0_gc | ((gain_mask&0x80) ? ADC_CH_MUXNEG_PIN6_gc :  ADC_CH_MUXNEG_PIN4_gc);
	#else
			ADCA.CH0.MUXCTRL = ((gain_mask&0x80) ? ADC_CH_MUXPOS_PIN2_gc :  ADC_CH_MUXPOS_PIN0_gc) | ((gain_mask&0x80) ? ADC_CH_MUXNEG_PIN6_gc :  ADC_CH_MUXNEG_PIN4_gc);
	#endif
	ADCA.CH0.INTCTRL = ADC_CH_INTLVL_OFF_gc;
	ADCA.CH0.SCAN = 0x00;  //Disable scanning
}

void tiny_adc_ch1setup(unsigned char gain_mask){
	ADCA.CH2.CTRL = 0x00; //Reset
	ADCA.CH2.CTRL = ADC_CH_START_bm | gain_mask | ADC_CH_INPUTMODE_DIFFWGAIN_gc;
	ADCA.CH2.MUXCTRL = ADC_CH_MUXPOS_PIN2_gc | ADC_CH_MUXNEG_PIN4_gc;
	ADCA.CH2.INTCTRL = ADC_CH_INTLVL_OFF_gc;
	ADCA.CH2.SCAN = 0x00;  //Disable scanning
}

void tiny_adc_pid_setup(void){
	ADCA.CH1.CTRL = 0x00; //Reset
	ADCA.CH1.CTRL = ADC_CH_START_bm | ADC_CH_GAIN_1X_gc | ADC_CH_INPUTMODE_DIFFWGAIN_gc;
	ADCA.CH1.MUXCTRL = ADC_CH_MUXPOS_PIN5_gc | 0b00000111;
	ADCA.CH1.INTCTRL = ADC_CH_INTLVL_OFF_gc;
	ADCA.CH1.SCAN = 0x00;  //Disable scanning
}


//FROM: http://www.avrfreaks.net/forum/xmega-production-signature-row
uint8_t ReadCalibrationByte(uint8_t index){
	uint8_t result;

	/* Load the NVM Command register to read the calibration row. */
	NVM_CMD = NVM_CMD_READ_CALIB_ROW_gc;
	result = pgm_read_byte(index);

	/* Clean up NVM Command register. */
	NVM_CMD = NVM_CMD_NO_OPERATION_gc;

	return( result );
}

ISR(ADCA_CH0_vect){
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	ADCA.CH0.INTFLAGS = 0x01;
}
