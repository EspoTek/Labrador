clear
clear global
clear functions
global num_lc
num_lc = 0

global fastmode
fastmode = 0;

global dac_top;
dac_top = 3.2;

global global_dc_offset;
global_dc_offset = 5;

set(0,'RecursionLimit',100000)
setscopewindowsize(0.1, 0, 5)
setscopemode(0,0.5,0.5)
launchgui
pause(0.01)
max_n = 100000000;
%setpsu(0,1000)
global trip_state
trip_state = uint8(0)
%tiny_send_waveform(sin(linspace(0,2*pi, 128)),255,432)
%tiny_send_waveform(1:100, 255, 100)]
%signal_trip(3);
mex_usb_iso_loop
%%plot(saved_waveform)