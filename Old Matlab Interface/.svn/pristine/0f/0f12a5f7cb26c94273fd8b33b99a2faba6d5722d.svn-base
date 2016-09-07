function [] = tiny_send_waveform(waveform, amplitude, frequency);

global scope_mode
global gui_axes

offset = 375;
waveform = tiny_wave_conv(waveform, amplitude);
waveform = uint8(waveform);
%waveform;

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
%clk_setting;

%stairs(uint8(waveform));

% wavestring = [];
% for n=1:wave_length
%     wavestring = [wavestring [sprintf('%3d, ', waveform(n)) ' ']];
% end

%%Exception for mode 5
if (scope_mode ==5)
    mex_usb_send_control('40', 'a1', dec2hex(tccper), dec2hex(clk_setting), dec2hex(wave_length), uint8(waveform));
    stairs(gui_axes, waveform, 'y')
    set(gui_axes, 'Color', [0 0 0], 'Box', 'on', 'XColor', [1 1 1], 'Ycolor', [1 1 1]);
    return
end


mex_usb_send_control('40', 'a1', dec2hex(tccper), dec2hex(clk_setting + 16*offset), dec2hex(min(375,wave_length)), uint8(waveform(1:min(375,wave_length))));

if(wave_length>375)
    warning('\nWave Length > 375')
    mex_usb_send_control('40', 'a1', dec2hex(tccper), dec2hex(clk_setting + 16*(offset+750) + 32768), dec2hex(wave_length-375), uint8(waveform(376:end)));
end
    

% driverLocation = 'c:\libusbk\examples\open-device\debug\win32';
% command = [driverLocation '\open-device "03eb" "a000" "' command '" "' num2str(tccper) '" "' num2str(clk_setting) '" "' num2str(wave_length) '" "' wavestring '"']
% system(command);