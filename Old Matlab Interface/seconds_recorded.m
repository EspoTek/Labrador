function [returnval] = seconds_recorded()

global saved_waveform_ch1
global scope_mode

if scope_mode == 6 | scope_mode == 7
    returnval = (length(saved_waveform_ch1)-750)/750000
else
    returnval = (length(saved_waveform_ch1)-750)/375000
end