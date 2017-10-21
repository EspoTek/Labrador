/*
 * tiny_dac.c
 *
 * Created: 3/07/2015 1:06:44 PM
 *  Author: Esposch
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