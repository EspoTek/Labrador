/*
 * tiny_adc.h
 *
 * Created: 19/06/2015 7:15:32 PM
 *  Author: Esposch
 */ 


#ifndef TINY_ADC_H_
#define TINY_ADC_H_

#include <stdio.h>
#include <asf.h>

void tiny_adc_setup(unsigned char ch2_enable, unsigned char seven_fiddy_ksps);
void tiny_adc_ch0setup(unsigned char gain_mask);
void tiny_adc_ch1setup(unsigned char gain_mask);
uint8_t ReadCalibrationByte(uint8_t index);  //FROM: http://www.avrfreaks.net/forum/xmega-production-signature-row
void tiny_adc_pid_setup(void);



#endif /* TINY_ADC_H_ */