global scope_window_time
global gui_delay
global trigger

pause(0.001)
%Will be buggy with delay
delay_sec = get(gui_delay, 'Max') - get(gui_delay, 'Value');
delay_sample = delay_sec*(samplestoshow/scope_window_time);

first

if (length(buffer)>samplestoshow) & ((length(buffer) - first) > (floor(samplestoshow/2)))
    if (samplestoshow>500)
        temp_waveform = buffer((first - floor(samplestoshow/2)) : (samplestoshow/500) : (first + floor(samplestoshow/2)));
    else
        temp_waveform = buffer((first - floor(samplestoshow/2)) : (first + floor(samplestoshow/2)));
    end
    trigger.begin = length(buffer)
    trigger.state = 0;
    update_enable = 1
    cool_waveform = undofrontend(temp_waveform, channel);
    taxis = linspace(-scope_window_time-delay_sec,-delay_sec,length(cool_waveform));
    return
end

update_enable = 0
taxis = []
cool_waveform = []
pause(0.001)