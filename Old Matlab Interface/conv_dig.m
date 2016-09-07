function [taxis, temp_waveform] = conv_dig(buffer, samplestoshow)
global scope_window_time
global gui_delay

delay_sec = get(gui_delay, 'Max') - get(gui_delay, 'Value');
delay_sample = delay_sec*(samplestoshow/scope_window_time);

if length(buffer)>samplestoshow
    if (scope_window_time>(500/375000))
        temp_waveform = buffer((length(buffer) - samplestoshow - delay_sample):samplestoshow/500: (length(buffer) - delay_sample));
        temp_waveform = typecast(temp_waveform, 'uint8');
        temp_waveform = logical(bitand(temp_waveform,16));
    else
        throwaway = round((ceil(samplestoshow)-samplestoshow)*8);
        dig_samples = buffer((length(buffer) - samplestoshow - delay_sample) : (length(buffer) - delay_sample));
        dig_samples = typecast(dig_samples, 'uint8');
        temp_waveform = false(1,length(dig_samples)*8);
        temp_waveform(1:8:length(temp_waveform)) = bitand(dig_samples,128);
        temp_waveform(2:8:length(temp_waveform)) = bitand(dig_samples,64);
        temp_waveform(3:8:length(temp_waveform)) = bitand(dig_samples,32);
        temp_waveform(4:8:length(temp_waveform)) = bitand(dig_samples,16);
        temp_waveform(5:8:length(temp_waveform)) = bitand(dig_samples,8);
        temp_waveform(6:8:length(temp_waveform)) = bitand(dig_samples,4);
        temp_waveform(7:8:length(temp_waveform)) = bitand(dig_samples,2);
        temp_waveform(8:8:length(temp_waveform)) = bitand(dig_samples,1);

        temp_waveform = temp_waveform((throwaway+1):end);
        temp_waveform = temp_waveform(1:length(temp_waveform)/500:end);
    end
    taxis = linspace(-scope_window_time-delay_sec,-delay_sec,length(temp_waveform));
    return
end

taxis = [];
temp_waveform = [];