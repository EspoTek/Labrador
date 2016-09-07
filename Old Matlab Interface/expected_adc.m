function [res] = expected_adc(vout)

vinp = vout/11;
vinn = 0;
vref = 1.65;
gain = 1;
top = 128;

res = int16((vinp - vinn)/vref * gain * top);