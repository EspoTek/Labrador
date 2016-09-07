function [wave] = tiny_wave_conv(wave, amplitude);

global scope_mode
global global_dc_offset;

% switch(scope_mode)
%     case 0
%         max_length = 750;
%     case 1
%         max_length = 128;
%         warning('Nowhere to store scope data on device.  Only frequency will be transmitted.')
%     case 2
%         max_length = 128;
%         warning('Nowhere to store scope data on device.  Only frequency will be transmitted.')
%     case 3
%         max_length = 750;
%     case 4
%         max_length = 128;
%         warning('Nowhere to store scope data on device.  Only frequency will be transmitted.')
%     case 5
%         max_length = 1500;
%     case 6
%         max_length = 128;
%         warning('Nowhere to store scope data on device.  Only frequency will be transmitted.')
%     otherwise
%         error('Invalid scope_mode!')
% end

if scope_mode == 5
    max_length = 1500;
else
    max_length = 750;
end
 

if length(wave)>max_length
    wave=imresize(wave,max_length/length(wave));
    warning('Vector length is greater than max_length.  It has been scaled down.')
end

if (amplitude>255 | amplitude<0 | amplitude ~= round(amplitude))
    error('Amplitude must be an integer between 0 and 255 for an 8 bit waveform!')
end


if var(wave) ~= 0
    wave = wave - min(wave);
end
    wave = wave * (amplitude-global_dc_offset) / max(wave);
    wave = round(wave) + global_dc_offset