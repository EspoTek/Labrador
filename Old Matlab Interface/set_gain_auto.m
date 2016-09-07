global scope_mode
global scope_window_min
global scope_window_max

if scope_mode ~= 7
    gain = autogain(scope_window_min, scope_window_max)
    setscopemode(scope_mode, gain, gain)
    saved_waveform_ch1 = []
    saved_waveform_ch2 = []
end