function [] = setscopegain(channel, gain);


if(gain~=0.5 & gain~=1 & gain~=2 & gain~=4 & gain~=8 & gain~=16 & gain~=32 & gain~=64)
    error('Valid values of gain are 0.5, 1, 2, 4, 8, 16, 32, 64');
end

global scope_gain
scope_gain = gain;

gain_mask = uint8([]);

%%FIX THIS UP
if (gain == 1/2)
    gain_mask = 7*4;
else 
    gain_mask = log2(gain) * 4;
end

%fprintf('%s\n', dec2bin(gain_mask,8));

mex_usb_send_control('40', 'a6', dec2hex(channel), dec2hex(gain_mask), '0', '0');