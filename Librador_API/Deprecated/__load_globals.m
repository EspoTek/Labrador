fprintf("Loading the global variables...\n");
global vcc
vcc  = 3.3
global vref
vref = vcc/2
global R4
R4 = 75000
global R3
R3 = 1000000
global R2
R2 = 1000
global R1
R1 = 1000
global PSU_ADC_TOP 
PSU_ADC_TOP = 128
global FGEN_OFFSET
FGEN_OFFSET = 5
global FGEN_LIMIT
FGEN_LIMIT = 3.2
global CLOCK_FREQ
CLOCK_FREQ = 48000000
global DAC_SPS
DAC_SPS = 1000000
global ADC_SPS
ADC_SPS = 750000
global ADC_SPF #samples per frame
ADC_SPF = (ADC_SPS/1000)

fprintf("\n")