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
