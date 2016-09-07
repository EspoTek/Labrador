global gui_scope_running
global gui_cursor_mode
global gui_hori_cursor_a_pos
global gui_hori_cursor_b_pos
global gui_vert_cursor_a_pos
global gui_vert_cursor_b_pos
global scope_window_min
global gui_awg_waveform
global gui_awg_amplitude
global gui_awg_frequency
global gui_vo
global gui_ro
global gui_static_text_scope
global CH1_AC
global CH2_AC

global gui_awg_waveform_aux
global gui_awg_amplitude_aux
global gui_awg_frequency_aux

global scope_window_max


scope_window_min = 0;
scope_window_max = 5;

set_gain_auto;

global mode7_func
mode7_func = 'V';
global Rtest;
Rtest = 1;
global scope_filter_value
scope_filter_value = 1;
global scope_filter_enabled
scope_filter_enabled = 0;
gui_scope_running = 1;
gui_cursor_mode = 1;
gui_static_text_scope = 0;

gui_vert_cursor_a_pos = 0;
gui_vert_cursor_b_pos = 0;
gui_hori_cursor_a_pos = scope_window_min;
gui_hori_cursor_b_pos = scope_window_min;

gui_awg_waveform = 'sin(linspace(0,2*pi,128))';
gui_awg_amplitude = '3.3';
gui_awg_frequency = '50'

gui_awg_waveform_aux = 'sin(linspace(0,2*pi,128))';
gui_awg_amplitude_aux = '3.3';
gui_awg_frequency_aux = '50'

gui_vo = 0;
gui_ro = 1000;

CH1_AC = 0;
CH2_AC = 0;

global dig0
global dig1
global dig2
global dig3

dig0 = 0;
dig1 = 0;
dig2 = 0;
dig3 = 0;

global scope_window_time
scope_window_time = 1

first_gui