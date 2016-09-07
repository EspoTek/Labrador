        global scope_window_time
        global gui_delay
        
        update_enable = 1;

        delay_sec = get(gui_delay, 'Max') - get(gui_delay, 'Value');
        delay_sample = delay_sec*(samplestoshow/scope_window_time);
        global scope_filter_value
        global scope_filter_enabled
        
        nshow = 500;
        if(scope_filter_enabled)
            nshow = nshow + scope_filter_value;
        end
        
        if length(buffer)>samplestoshow
            if (samplestoshow>nshow)
                temp_waveform = buffer((length(buffer) - samplestoshow - delay_sample):samplestoshow/nshow: (length(buffer) - delay_sample));
            else
                temp_waveform = buffer((length(buffer) - samplestoshow - delay_sample): (length(buffer) - delay_sample));
            end
            cool_waveform = undofrontend(temp_waveform, channel);
            taxis = linspace(-scope_window_time-delay_sec,-delay_sec,length(cool_waveform));
            return
        end
        
        taxis = [];
        cool_waveform = [];
