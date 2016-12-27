/*
 * tiny_timercounter.c
 *
 * Created: 2/07/2015 10:50:11 AM
 *  Author: Esposch
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
		
		EVSYS.CH1MUX = EVSYS_CHMUX_ADCA_CH0_gc;
		EVSYS.CH1CTRL = 0x00; //No filtering or Quadrature stuff
		
		EVSYS.CH0MUX = EVSYS_CHMUX_ADCA_CH2_gc;
		EVSYS.CH0CTRL = 0x00; //No filtering or Quadrature stuff

			
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