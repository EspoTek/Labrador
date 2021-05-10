/*
 * tiny_timercounter.c
 *
 * Created: 2/07/2015 10:50:11 AM
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

#include "tiny_timer.h"
#include "globals.h"

#define PSU_PER 2048
#define jump 6

void tiny_timer_setup(void){
	//Turn everything on!
		PR.PRPC &= 0b11111100; //Enable TCC0, TCC1
		PR.PRPD &= 0b11111100; //Enable TCD0, TCD1
		PR.PRGEN &= 0b11111101; //Enable EVSYS

	//Set up EVSYS
		EVSYS.CH2MUX = TCDAC_OVF;
		EVSYS.CH2CTRL = 0x00; //No filtering or Quadrature stuff

		EVSYS.CH1MUX = TCDAC_AUX_OVF;
		EVSYS.CH1CTRL = 0x00; //No filtering or Quadrature stuff

	//Waveform (50Hz sin wave)
		TC_DAC.CTRLA = 0x04; //Some clk setting - not 100% sure since it was SW generated
		TC_DAC.CTRLB = TC_WGMODE_SINGLESLOPE_gc;  //No enable is set
		TC_DAC.CTRLE = TC_BYTEM_NORMAL_gc;
		TC_DAC.PER = 469;
		TC_DAC.INTCTRLA = 0x00;
	//Aux channel (blank 50Hz)
		TC_AUXDAC.CTRLA = 0x04; //Some clk setting - not 100% sure since it was SW generated
		TC_AUXDAC.CTRLB = TC_WGMODE_SINGLESLOPE_gc;  //No enable is set
		TC_AUXDAC.CTRLE = TC_BYTEM_NORMAL_gc;
		TC_AUXDAC.PER = 469;
		TC_AUXDAC.INTCTRLA = 0x00;

	//PSU
		PORTD.DIR |= 0b00010000;
		TC_PSU.CTRLB = 0x10 | TC_WGMODE_SINGLESLOPE_gc;  //CCAEN is set
		TC_PSU.CTRLE = TC_BYTEM_NORMAL_gc;
		TC_PSU.INTCTRLA = TC_OVFINTLVL_MED_gc;
		TC_PSU.PER = PSU_PER;  // Max value of CNT
		TC_PSU.CCA = 0; //Initial Duty cycle of 0%
		TC_PSU.CTRLA = TC_CLKSEL_DIV1_gc;
	/*
	//PSU "PID"loop
		TCC1.CTRLB = 0x00 | TC_WGMODE_SINGLESLOPE_gc;
		TCC1.INTCTRLA = TC_OVFINTLVL_LO_gc;
		TCC1.CTRLE = TC_BYTEM_NORMAL_gc;
		TCC1.PER = 1800;  // Max value of CNT
		TCC1.CTRLA = TC_CLKSEL_DIV1_gc;
		*/
}

ISR(TC_PSU_OVF){
	char tempvar;
	char err;
	volatile char nothing;
	TC_PSU.INTFLAGS = 0xff;
	if (global_mode == 7){
		nothing = ADCA.CH1.RESL;
		tempvar = ADCA.CH1.RESH;
	}
	else{
		tempvar = ADCA.CH1.RESL;
	}
	//tempvar = (global_mode == 7 ? (char) ADCA.CH1.RESH : (char) ADCA.CH1.RESL);
	//test_byte = tempvar;

	err = (char) (PSU_target - tempvar);
	if ((err > 1) & ((unsigned short) TC_PSU.CCA < PSU_PER - jump) ){
		TC_PSU.CCABUF = TC_PSU.CCA + ((err > 8) ? jump : 1);
	}
	else if ((err < -1) & ((unsigned short) TC_PSU.CCA > jump)){
		TC_PSU.CCABUF = TC_PSU.CCA - ((err < -8) ? jump : 1);
	}
}
