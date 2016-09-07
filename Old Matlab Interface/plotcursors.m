global gui_hori_cursor_a_pos
global gui_hori_cursor_b_pos
global gui_vert_cursor_a_pos
global gui_vert_cursor_b_pos
global scope_window_time
global scope_window_max
global scope_window_min

global gui_cursor_mode
global gui_axes
global scope_mode
global gui_delay

global fastmode
 
delay_sec = get(gui_delay, 'Max') - get(gui_delay, 'Value')

gui_cursor_mode;

if(scope_mode==2)
    switch(gui_cursor_mode)
        case 1
            plot(gui_axes, taxis_ch1, cool_waveform_ch1, 'y', taxis_ch2, cool_waveform_ch2, 'c');
        case 2
            plot(gui_axes, taxis_ch1, cool_waveform_ch1, 'y', taxis_ch2, cool_waveform_ch2, 'c', [-scope_window_time-delay_sec, -delay_sec], [gui_hori_cursor_a_pos gui_hori_cursor_a_pos], 'w', [-scope_window_time-delay_sec, -delay_sec], [gui_hori_cursor_b_pos gui_hori_cursor_b_pos], 'w:');
        case 3
            plot(gui_axes, taxis_ch1, cool_waveform_ch1, 'y', taxis_ch2, cool_waveform_ch2, 'c', [gui_vert_cursor_a_pos-delay_sec gui_vert_cursor_a_pos-delay_sec], [scope_window_min scope_window_max], 'w', [gui_vert_cursor_b_pos-delay_sec gui_vert_cursor_b_pos-delay_sec], [scope_window_min scope_window_max], 'w:');
        case 4
            plot(gui_axes, taxis_ch1, cool_waveform_ch1, 'y', taxis_ch2, cool_waveform_ch2, 'c', [gui_vert_cursor_a_pos-delay_sec gui_vert_cursor_a_pos-delay_sec], [scope_window_min scope_window_max], 'w', [gui_vert_cursor_b_pos-delay_sec gui_vert_cursor_b_pos-delay_sec], [scope_window_min scope_window_max], 'w:', [-scope_window_time-delay_sec -delay_sec], [gui_hori_cursor_a_pos gui_hori_cursor_a_pos], 'w', [-scope_window_time-delay_sec -delay_sec], [gui_hori_cursor_b_pos gui_hori_cursor_b_pos], 'w:');
        otherwise
            error('Gui_axes is in an invalid state');
    end
else
    switch(gui_cursor_mode)
        case 1
            plot(gui_axes, taxis, cool_waveform, 'y');
        case 2
            plot(gui_axes, taxis, cool_waveform, 'y', [-scope_window_time-delay_sec, -delay_sec], [gui_hori_cursor_a_pos gui_hori_cursor_a_pos], 'w', [-scope_window_time-delay_sec, -delay_sec], [gui_hori_cursor_b_pos gui_hori_cursor_b_pos], 'w:');
        case 3
            plot(gui_axes, taxis, cool_waveform, 'y', [gui_vert_cursor_a_pos-delay_sec gui_vert_cursor_a_pos-delay_sec], [scope_window_min scope_window_max], 'w', [gui_vert_cursor_b_pos-delay_sec gui_vert_cursor_b_pos-delay_sec], [scope_window_min scope_window_max], 'w:');
        case 4
            plot(gui_axes, taxis, cool_waveform, 'y', [gui_vert_cursor_a_pos-delay_sec gui_vert_cursor_a_pos-delay_sec], [scope_window_min scope_window_max], 'w', [gui_vert_cursor_b_pos-delay_sec gui_vert_cursor_b_pos-delay_sec], [scope_window_min scope_window_max], 'w:', [-scope_window_time-delay_sec -delay_sec], [gui_hori_cursor_a_pos gui_hori_cursor_a_pos], 'w', [-scope_window_time-delay_sec -delay_sec], [gui_hori_cursor_b_pos gui_hori_cursor_b_pos], 'w:');
        otherwise
            error('Gui_axes is in an invalid state');
    end
end

set(gui_axes, 'Ylim', [scope_window_min, scope_window_max], 'Xlim', [-scope_window_time-delay_sec, -delay_sec], 'Color', [0 0 0], 'Box', 'on', 'XColor', [1 1 1], 'Ycolor', [1 1 1], 'ButtonDownFcn', 'axes1_ButtonDownFcn');
%set(gui_axes, );
%disp('SET!!!')