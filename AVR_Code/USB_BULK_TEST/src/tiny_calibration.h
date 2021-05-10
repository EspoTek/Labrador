/*
 * tiny_calibration.h
 *
 * Created: 9/01/2017 4:21:09 PM
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


#ifndef TINY_CALIBRATION_H_
#define TINY_CALIBRATION_H_

#include <asf.h>
#include <stdio.h>

void tiny_calibration_init();
void tiny_calibration_first_sof();
void tiny_calibration_maintain();
void tiny_calibration_safe_add(int rawValue);
int tiny_distance_from_centre(unsigned int point);
void tiny_calibration_find_values();
void tiny_calibration_layer2();
unsigned int magnitude_difference(unsigned int a, unsigned int b);
void tiny_calibration_synchronise_phase(unsigned int phase, unsigned int precision);

extern volatile unsigned char calibration_values_found;
extern volatile unsigned char median_TRFCNT_delay;

volatile unsigned char cali_value_negative_gradient;
volatile unsigned char cali_value_positive_gradient;


#endif /* TINY_CALIBRATION_H_ */
