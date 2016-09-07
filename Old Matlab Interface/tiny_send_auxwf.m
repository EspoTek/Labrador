function [] = tiny_send_auxwf(waveform, amplitude, frequency);

waveform = tiny_wave_conv_aux(waveform, amplitude);
waveform = uint8(waveform);

wave_length = length(waveform);

f_invalid = 1;

valid_clock_div = [1,2,4,8,64,256,1024];
f0=24e6;

if(frequency*wave_length)>1e6
    error('Frequency is too high')
end

for clk_setting = 1:length(valid_clock_div)
    f_test = f0 / valid_clock_div(clk_setting);
    if (f_test/frequency)<65535
        f_invalid = 0;
        break
    end
end

if (f_invalid)
    error('Frequency is too low!')
end

tccper = round(f_test / frequency / wave_length);
tccper = uint16(tccper);

clk_setting = uint16(clk_setting);

waveform
mex_usb_send_control('40', 'a2', dec2hex(tccper), dec2hex(clk_setting), dec2hex(wave_length), waveform);

