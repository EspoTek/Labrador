function [taxis, cool_waveform, update_enable] = conv_ana(buffer, samplestoshow, channel)

        global scope_window_time
        global gui_delay
        global trigger
        
        if trigger.enabled==0
            conv_ana_notrig;
        else
            lo = dofrontend(trigger.l, channel)
            hi = dofrontend(trigger.h, channel)
            state = trigger.state
            begin = max(trigger.begin, ceil(samplestoshow/2))
            
            if state==0 %looking to fall
                first = find(buffer(begin:end)<lo, 1, 'first')
                trigger.state = ~isempty(first)
                trigger.begin = length(buffer) + 1
                taxis = []
                cool_waveform = []
                update_enable = 0
            else
                first = find(buffer(begin:end)>hi, 1, 'first') + begin
                if ~isempty(first)
                    draw_triggered;
                else
                    taxis = []
                    cool_waveform = []
                    update_enable = 0
                    pause(0.001)
                end
            end
        end
        return
        
        
        
