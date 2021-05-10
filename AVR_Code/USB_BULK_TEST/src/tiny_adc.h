/*
 * tiny_adc.h
 *
 * Created: 19/06/2015 7:15:32 PM
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
