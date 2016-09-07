global num_lc
global gui_static_text_scope
global saved_waveform_ch1
global saved_waveform_ch2
global usb_handle
global gui_delay

num_lc = num_lc + 1;
max_n = 100000000;
%USB_POOL_FREE(ovlPool, ovlkHandle_0, ovlkHandle_1, usb_handle);  //It
%crashes when I clear the handles.  No idea why, but it's fine when I don't
clear usb_handle
set(gui_static_text_scope, 'String', sprintf('THE SCOPE (Reconnected %d times)', num_lc));
saved_waveform_ch1 = []
saved_waveform_ch2 = []
set(gui_delay, 'Value', get(gui_delay, 'Max'));

mex_usb_iso_loop

