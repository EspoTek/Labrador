// Copyright (C) 2017, 2018, 2019, 2020, 2021 Christopher Paul Esposito
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef XMEGA_H
#define XMEGA_H

//Just a whole lot of variables related to the hardware itself.

#define FGEN_OFFSET 5
#define FGEN_LIMIT (double) 3.2
#define CLOCK_FREQ 48000000
#define DAC_SPS 1000000
#define ADC_SPS 750000
#define ADC_SPF (ADC_SPS/1000)

#define vcc (double)3.3
#define vref ((double)(vcc/2))
#define R4 (double)75000
#define R3 (double)1000000
#define R2 (double)1000
#define R1 (double)1000

#define INIT_DEVICE_MODE 0

#define PSU_STEP 5
#define PSU_PERIOD 100
#define PSU_ADC_TOP 128

#define INVERT_TRIPLE
#define INVERT_MM

#endif // XMEGA_H
