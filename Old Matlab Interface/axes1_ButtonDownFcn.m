function axes1_ButtonDownFcn()

persistent state
if isempty(state)
    state = 0;
end

global gui_hori_cursor_a_pos
global gui_hori_cursor_b_pos
global gui_vert_cursor_a_pos
global gui_vert_cursor_b_pos
global gui_figure1
%gui_hori_cursor_a_pos = scope_window_min + (scope_window_max - scope_window_min) * get(hObject,'Value');


clicktype = get(gui_figure1,'selectionType');
pos = get (gca, 'CurrentPoint');
pos = [pos(1,1), pos(1,2)]

global gui_delay
delay_sec = get(gui_delay, 'Max') - get(gui_delay, 'Value')


switch (clicktype)
    case 'normal'
        switch(state)
            case 0
                state=1;
                gui_hori_cursor_a_pos = pos(2);
            case 1
                state=0;
                gui_hori_cursor_b_pos = pos(2);
            otherwise
                state = 0;
        end
        fprintf('LEFT CLICK @(%.2f, %.2f)\n', pos(1), pos(2))
    case 'alt'
        switch(state)
            case 0
                state=3;
                gui_vert_cursor_a_pos = pos(1) + delay_sec;
            case 3
                state=0;
                gui_vert_cursor_b_pos = pos(1) + delay_sec;
            otherwise
                state = 0;
        end
        fprintf('RIGHT CLICK @(%.2f, %.2f)\n', pos(1), pos(2))
    otherwise
        disp('OTHER')
end

%disp('settan')

global gui_cursor_mode
global text_box_2

switch gui_cursor_mode
    case 1
        set(text_box_2, 'String', sprintf(' Vertical Cursor Disabled\n Vertical Cursor Disabled\n Vertical Cursor Disabled\n  \n Horizontal cursor disabled \n Horizontal cursor disabled \n Horizontal cursor disabled \n '))
    case 2
        set(text_box_2, 'String', sprintf(' Vertical Cursor Disabled\n Vertical Cursor Disabled\n Vertical Cursor Disabled\n  \n V1 = %s\n V2 = %s\n DeltaV = %s\n', sisprintf(gui_hori_cursor_a_pos,'V',3), sisprintf(gui_hori_cursor_b_pos,'V',3), sisprintf(gui_hori_cursor_a_pos - gui_hori_cursor_b_pos,'V',3)))
    case 3
        set(text_box_2, 'String', sprintf(' T1 = %s\n T2 = %s\n DeltaT = %s\n \n Horizontal cursor disabled \n Horizontal cursor disabled \n Horizontal cursor disabled \n ', sisprintf(gui_vert_cursor_a_pos,'s',3), sisprintf(gui_vert_cursor_b_pos,'s',3), sisprintf(gui_vert_cursor_a_pos - gui_vert_cursor_b_pos,'s',3)))
    case 4
        set(text_box_2, 'String', sprintf(' T1 = %s\n T2 = %s\n DeltaT = %s\n \n V1 = %s\n V2 = %s\n DeltaV = %s\n', sisprintf(gui_vert_cursor_a_pos,'s',3), sisprintf(gui_vert_cursor_b_pos,'s',3), sisprintf(gui_vert_cursor_a_pos - gui_vert_cursor_b_pos,'s',3), sisprintf(gui_hori_cursor_a_pos,'V',3), sisprintf(gui_hori_cursor_b_pos,'V',3), sisprintf(gui_hori_cursor_a_pos - gui_hori_cursor_b_pos,'V',3)))
    otherwise error('Gui_cursor_mode is invalid')
end