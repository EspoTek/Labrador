function [wave] = tiny_wave_conv_aux(wave, amplitude);
global global_dc_offset

if length(wave)>128
    wave=imresize(wave,128/length(wave));
    warning('Vector length is greater than max_length.  It has been scaled down.')
end

if (amplitude>255 | amplitude<0 | amplitude ~= round(amplitude))
    error('Amplitude must be an integer between 0 and 255 for an 8 bit waveform!')
end

if var(wave) ~= 0
    wave = wave - min(wave);
end
    wave = wave * (amplitude-global_dc_offset) / max(wave);
    wave = round(wave) + global_dc_offset;