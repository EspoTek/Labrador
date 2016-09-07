function varargout = first_gui(varargin)
% FIRST_GUI MATLAB code for first_gui.fig
%      FIRST_GUI, by itself, creates a new FIRST_GUI or raises the existing
%      singleton*.
%
%      H = FIRST_GUI returns the handle to a new FIRST_GUI or the handle to
%      the existing singleton*.
%
%      FIRST_GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in FIRST_GUI.M with the given input arguments.
%
%      FIRST_GUI('Property','Value',...) creates a new FIRST_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before first_gui_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to first_gui_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help first_gui

% Last Modified by GUIDE v2.5 26-Feb-2016 12:00:46

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @first_gui_OpeningFcn, ...
                   'gui_OutputFcn',  @first_gui_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before first_gui is made visible.
function first_gui_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to first_gui (see VARARGIN)

% Choose default command line output for first_gui
handles.output = hObject;

handles

movegui(handles.figure1,[128,128]) 

global gui_axes
global gui_delay
global text_box_1
global text_box_2
global text_box_c
global gui_figure1

text_box_c = handles.text14;

gui_delay = handles.slider6
gui_axes = handles.axes1;
text_box_1 = handles.edit1;
text_box_2 = handles.text9;
gui_figure1 = handles.figure1;



%get(handles.axes1)

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes first_gui wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = first_gui_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



function edit1_Callback(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit1 as text
%        str2double(get(hObject,'String')) returns contents of edit1 as a double


% --- Executes during object creation, after setting all properties.
function edit1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit2_Callback(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit2 as text
%        str2double(get(hObject,'String')) returns contents of edit2 as a double


% --- Executes during object creation, after setting all properties.
function edit2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit3_Callback(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit3 as text
%        str2double(get(hObject,'String')) returns contents of edit3 as a double


% --- Executes during object creation, after setting all properties.
function edit3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit4_Callback(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit4 as text
%        str2double(get(hObject,'String')) returns contents of edit4 as a double


% --- Executes during object creation, after setting all properties.
function edit4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on slider movement.
function slider1_Callback(hObject, eventdata, handles)
global scope_window_time
global gui_delay
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
scope_window_time = 10^(-get(hObject, 'value'))
set(gui_delay, 'SliderStep', [scope_window_time/100, scope_window_time/10]);
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end



function edit5_Callback(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit5 as text
%        str2double(get(hObject,'String')) returns contents of edit5 as a double


% --- Executes during object creation, after setting all properties.
function edit5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on slider movement.
function slider2_Callback(hObject, eventdata, handles)
% hObject    handle to slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global gui_hori_cursor_a_pos
global scope_window_max
global scope_window_min 
global text_box_2
global gui_cursor_mode

gui_hori_cursor_a_pos = scope_window_min + (scope_window_max - scope_window_min) * get(hObject,'Value');

global gui_hori_cursor_b_pos
global gui_vert_cursor_a_pos
global gui_vert_cursor_b_pos
switch gui_cursor_mode
    case 1
        set(text_box_2, 'String', sprintf(' Vertical Cursor Disabled\n Vertical Cursor Disabled\n Vertical Cursor Disabled\n  \n Horizontal cursor disabled \n Horizontal cursor disabled \n Horizontal cursor disabled \n '))
    case 2
        set(text_box_2, 'String', sprintf(' Vertical Cursor Disabled\n Vertical Cursor Disabled\n Vertical Cursor Disabled\n  \n V1 = %s\n V2 = %s\n DeltaV = %s\n', sisprintf(gui_hori_cursor_a_pos,'V',3), sisprintf(gui_hori_cursor_b_pos,'V',3), sisprintf(gui_hori_cursor_a_pos - gui_hori_cursor_b_pos,'V',3)))
    case 3
        set(text_box_2, 'String', sprintf(' T1 = %s\n T2 = %s\n DeltaT = %s\n \n Horizontal cursor disabled \n Horizontal cursor disabled \n Horizontal cursor disabled \n ', sisprintf(gui_vert_cursor_a_pos,'s',3), sisprintf(gui_vert_cursor_b_pos,'s',3), sisprintf(gui_vert_cursor_a_pos - gui_vert_cursor_b_pos,'s',3)))
    case 4
        set(text_box_2, 'String', sprintf(' T1 = %s\n T2 = %s\n DeltaT = %s\n \n V1 = %s\n V2 = %s\n DeltaV = %s\n', sisprintf(gui_vert_cursor_a_pos,'s',3), sisprintf(gui_vert_cursor_b_pos,'s',3), sisprintf(gui_vert_cursor_a_pos - gui_vert_cursor_b_pos,'s',3), sisprintf(gui_hori_cursor_a_pos,'v',3), sisprintf(gui_hori_cursor_b_pos,'v',3), sisprintf(gui_hori_cursor_a_pos - gui_hori_cursor_b_pos,'v',3)))
    otherwise error('Gui_cursor_mode is invalid')
end
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on selection change in popupmenu1.
function popupmenu1_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global gui_cursor_mode
gui_cursor_mode = get(hObject,'Value')

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu1 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu1


% --- Executes during object creation, after setting all properties.
function popupmenu1_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on slider movement.
function slider3_Callback(hObject, eventdata, handles)
% hObject    handle to slider3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global gui_hori_cursor_b_pos
global scope_window_max
global scope_window_min 
global text_box_2
global gui_cursor_mode

gui_hori_cursor_b_pos = scope_window_min + (scope_window_max - scope_window_min) * get(hObject,'Value');

global gui_hori_cursor_a_pos
global gui_vert_cursor_a_pos
global gui_vert_cursor_b_pos
switch gui_cursor_mode
    case 1
        set(text_box_2, 'String', sprintf(' Vertical Cursor Disabled\n Vertical Cursor Disabled\n Vertical Cursor Disabled\n  \n Horizontal cursor disabled \n Horizontal cursor disabled \n Horizontal cursor disabled \n '))
    case 2
        set(text_box_2, 'String', sprintf(' Vertical Cursor Disabled\n Vertical Cursor Disabled\n Vertical Cursor Disabled\n  \n V1 = %s\n V2 = %s\n DeltaV = %s\n', sisprintf(gui_hori_cursor_a_pos,'V',3), sisprintf(gui_hori_cursor_b_pos,'V',3), sisprintf(gui_hori_cursor_a_pos - gui_hori_cursor_b_pos,'V',3)))
    case 3
        set(text_box_2, 'String', sprintf(' T1 = %s\n T2 = %s\n DeltaT = %s\n \n Horizontal cursor disabled \n Horizontal cursor disabled \n Horizontal cursor disabled \n ', sisprintf(gui_vert_cursor_a_pos,'s',3), sisprintf(gui_vert_cursor_b_pos,'s',3), sisprintf(gui_vert_cursor_a_pos - gui_vert_cursor_b_pos,'s',3)))
    case 4
        set(text_box_2, 'String', sprintf(' T1 = %s\n T2 = %s\n DeltaT = %s\n \n V1 = %s\n V2 = %s\n DeltaV = %s\n', sisprintf(gui_vert_cursor_a_pos,'s',3), sisprintf(gui_vert_cursor_b_pos,'s',3), sisprintf(gui_vert_cursor_a_pos - gui_vert_cursor_b_pos,'s',3), sisprintf(gui_hori_cursor_a_pos,'v',3), sisprintf(gui_hori_cursor_b_pos,'v',3), sisprintf(gui_hori_cursor_a_pos - gui_hori_cursor_b_pos,'v',3)))
    otherwise error('Gui_cursor_mode is invalid')
end
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end



function edit6_Callback(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global gui_awg_waveform
gui_awg_waveform = get(hObject,'String');


% Hints: get(hObject,'String') returns contents of edit6 as text
%        str2double(get(hObject,'String')) returns contents of edit6 as a double


% --- Executes during object creation, after setting all properties.
function edit6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global gui_awg_waveform
global gui_awg_amplitude
global gui_awg_frequency
global scope_mode

gui_awg_waveform
gui_awg_amplitude
gui_awg_frequency
if scope_mode == 0 | scope_mode == 3 | scope_mode == 5
    tiny_send_waveform(eval(gui_awg_waveform), amp2bin(str2num(gui_awg_amplitude),1), str2num(gui_awg_frequency));
    fprintf('\nStandard\n')
else
    error('Can''t send, breh!')
end


function edit7_Callback(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global gui_awg_amplitude
gui_awg_amplitude = get(hObject,'String');

% Hints: get(hObject,'String') returns contents of edit7 as text
%        str2double(get(hObject,'String')) returns contents of edit7 as a double


% --- Executes during object creation, after setting all properties.
function edit7_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit8_Callback(hObject, eventdata, handles)
% hObject    handle to edit8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global gui_awg_frequency
gui_awg_frequency = get(hObject,'String');
% Hints: get(hObject,'String') returns contents of edit8 as text
%        str2double(get(hObject,'String')) returns contents of edit8 as a double


% --- Executes during object creation, after setting all properties.
function edit8_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit8 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.

if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton4.
function pushbutton4_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global gui_scope_running
gui_scope_running = ~gui_scope_running



function edit9_Callback(hObject, eventdata, handles)
% hObject    handle to edit9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global gui_vo;
gui_vo = str2num(get(hObject, 'String'));
setpsu_boost(gui_vo);


% Hints: get(hObject,'String') returns contents of edit9 as text
%        str2double(get(hObject,'String')) returns contents of edit9 as a double


% --- Executes during object creation, after setting all properties.
function edit9_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit10_Callback(hObject, eventdata, handles)
% hObject    handle to edit10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global gui_ro;
gui_ro = str2num(get(hObject, 'String'));
% Hints: get(hObject,'String') returns contents of edit10 as text
%        str2double(get(hObject,'String')) returns contents of edit10 as a double


% --- Executes during object creation, after setting all properties.
function edit10_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton5.
function pushbutton5_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on slider movement.
function slider4_Callback(hObject, eventdata, handles)
% hObject    handle to slider4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global gui_vert_cursor_a_pos
global scope_window_time
global text_box_2
global gui_cursor_mode

gui_vert_cursor_a_pos = -scope_window_time + (scope_window_time) * get(hObject,'Value');

global gui_hori_cursor_a_pos
global gui_hori_cursor_b_pos
global gui_vert_cursor_b_pos
switch gui_cursor_mode
    case 1
        set(text_box_2, 'String', sprintf(' Vertical Cursor Disabled\n Vertical Cursor Disabled\n Vertical Cursor Disabled\n  \n Horizontal cursor disabled \n Horizontal cursor disabled \n Horizontal cursor disabled \n '))
    case 2
        set(text_box_2, 'String', sprintf(' Vertical Cursor Disabled\n Vertical Cursor Disabled\n Vertical Cursor Disabled\n  \n V1 = %s\n V2 = %s\n DeltaV = %s\n', sisprintf(gui_hori_cursor_a_pos,'V',3), sisprintf(gui_hori_cursor_b_pos,'V',3), sisprintf(gui_hori_cursor_a_pos - gui_hori_cursor_b_pos,'V',3)))
    case 3
        set(text_box_2, 'String', sprintf(' T1 = %s\n T2 = %s\n DeltaT = %s\n \n Horizontal cursor disabled \n Horizontal cursor disabled \n Horizontal cursor disabled \n ', sisprintf(gui_vert_cursor_a_pos,'s',3), sisprintf(gui_vert_cursor_b_pos,'s',3), sisprintf(gui_vert_cursor_a_pos - gui_vert_cursor_b_pos,'s',3)))
    case 4
        set(text_box_2, 'String', sprintf(' T1 = %s\n T2 = %s\n DeltaT = %s\n \n V1 = %s\n V2 = %s\n DeltaV = %s\n', sisprintf(gui_vert_cursor_a_pos,'s',3), sisprintf(gui_vert_cursor_b_pos,'s',3), sisprintf(gui_vert_cursor_a_pos - gui_vert_cursor_b_pos,'s',3), sisprintf(gui_hori_cursor_a_pos,'v',3), sisprintf(gui_hori_cursor_b_pos,'v',3), sisprintf(gui_hori_cursor_a_pos - gui_hori_cursor_b_pos,'v',3)))
    otherwise error('Gui_cursor_mode is invalid')
end
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on slider movement.
function slider5_Callback(hObject, eventdata, handles)
% hObject    handle to slider5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global gui_vert_cursor_b_pos
global scope_window_time
global text_box_2
global gui_cursor_mode
gui_vert_cursor_b_pos = -scope_window_time + (scope_window_time) * get(hObject,'Value');

global gui_hori_cursor_a_pos
global gui_hori_cursor_b_pos
global gui_vert_cursor_a_pos
switch gui_cursor_mode
    case 1
        set(text_box_2, 'String', sprintf(' Vertical Cursor Disabled\n Vertical Cursor Disabled\n Vertical Cursor Disabled\n  \n Horizontal cursor disabled \n Horizontal cursor disabled \n Horizontal cursor disabled \n '))
    case 2
        set(text_box_2, 'String', sprintf(' Vertical Cursor Disabled\n Vertical Cursor Disabled\n Vertical Cursor Disabled\n  \n V1 = %s\n V2 = %s\n DeltaV = %s\n', sisprintf(gui_hori_cursor_a_pos,'V',3), sisprintf(gui_hori_cursor_b_pos,'V',3), sisprintf(gui_hori_cursor_a_pos - gui_hori_cursor_b_pos,'V',3)))
    case 3
        set(text_box_2, 'String', sprintf(' T1 = %s\n T2 = %s\n DeltaT = %s\n \n Horizontal cursor disabled \n Horizontal cursor disabled \n Horizontal cursor disabled \n ', sisprintf(gui_vert_cursor_a_pos,'s',3), sisprintf(gui_vert_cursor_b_pos,'s',3), sisprintf(gui_vert_cursor_a_pos - gui_vert_cursor_b_pos,'s',3)))
    case 4
        set(text_box_2, 'String', sprintf(' T1 = %s\n T2 = %s\n DeltaT = %s\n \n V1 = %s\n V2 = %s\n DeltaV = %s\n', sisprintf(gui_vert_cursor_a_pos,'s',3), sisprintf(gui_vert_cursor_b_pos,'s',3), sisprintf(gui_vert_cursor_a_pos - gui_vert_cursor_b_pos,'s',3), sisprintf(gui_hori_cursor_a_pos,'v',3), sisprintf(gui_hori_cursor_b_pos,'v',3), sisprintf(gui_hori_cursor_a_pos - gui_hori_cursor_b_pos,'v',3)))
    otherwise error('Gui_cursor_mode is invalid')
end
% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on selection change in popupmenu2.
function popupmenu2_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global scope_mode
global scope_gain_0
global scope_gain_1
global refreshrate
global refreshrate_temp
global waveform_exists
global saved_waveform_ch1
global saved_waveform_ch2
global gui_delay

refreshrate_temp = refreshrate;
waveform_exists = 0

contents = cellstr(get(hObject,'String'));
tempstring = contents{get(hObject,'Value')};

mode = str2num(tempstring(6));
setscopemode(mode, scope_gain_0, scope_gain_1)

saved_waveform_ch1 = [];
saved_waveform_ch2 = [];
set(gui_delay, 'Value', get(gui_delay, 'Max'))

if(mode==7)
    set(handles.popupmenu3, 'Visible', 'on')
    set(handles.popupmenu4, 'Visible', 'on')
    set(handles.popupmenu7, 'Visible', 'on')
else
    set(handles.popupmenu3, 'Visible', 'off')
    set(handles.popupmenu4, 'Visible', 'off')
    set(handles.popupmenu7, 'Visible', 'off')
    set_gain_auto
end

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu2


% --- Executes during object creation, after setting all properties.
function popupmenu2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on slider movement.
function slider6_Callback(hObject, eventdata, handles)
% hObject    handle to slider6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider


% --- Executes during object creation, after setting all properties.
function slider6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
set(hObject,'Value', 1);



function edit11_Callback(hObject, eventdata, handles)
% hObject    handle to edit11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global gui_delay

boxvar = str2num(get(hObject,'String'));
if boxvar<seconds_recorded
    negative_slider = min(boxvar, get(gui_delay, 'Max') - get(gui_delay, 'Value'));
    set(gui_delay, 'Max', boxvar);
    set(gui_delay, 'Value', boxvar - negative_slider);   
else
    set(hObject, 'String', sprintf('%.2f', get(gui_delay, 'Max')));
end

% Hints: get(hObject,'String') returns contents of edit11 as text
%        str2double(get(hObject,'String')) returns contents of edit11 as a double


% --- Executes during object creation, after setting all properties.
function edit11_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit11 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu3.
function popupmenu3_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global scope_gain_0
global scope_gain_1
global scope_mode

contents = cellstr(get(hObject,'String'));
newgain = str2num(contents{get(hObject,'Value')});
setscopemode(scope_mode, newgain, scope_gain_1)
saved_waveform_ch1 = []

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu3 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu3


% --- Executes during object creation, after setting all properties.
function popupmenu3_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu4.
function popupmenu4_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global scope_gain_0
global scope_gain_1
global scope_mode

get(hObject)
contents = cellstr(get(hObject,'String'));
newgain = str2num(contents{get(hObject,'Value')});
setscopemode(scope_mode, scope_gain_0, newgain)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu4 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu4


% --- Executes during object creation, after setting all properties.
function popupmenu4_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit12_Callback(hObject, eventdata, handles)
% hObject    handle to edit12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global scope_window_time
global scope_window_min
global scope_window_max

value = str2num(get(hObject,'String'));
setscopewindowsize(scope_window_time, value, scope_window_max)
set_gain_auto


% Hints: get(hObject,'String') returns contents of edit12 as text
%        str2double(get(hObject,'String')) returns contents of edit12 as a double


% --- Executes during object creation, after setting all properties.
function edit12_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit14_Callback(hObject, eventdata, handles)
% hObject    handle to edit14 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global scope_window_time
global scope_window_min
global scope_window_max

value = str2num(get(hObject,'String'));
setscopewindowsize(scope_window_time, scope_window_min, value)
set_gain_auto

% Hints: get(hObject,'String') returns contents of edit14 as text
%        str2double(get(hObject,'String')) returns contents of edit14 as a double


% --- Executes during object creation, after setting all properties.
function edit14_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit14 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in togglebutton1.
function togglebutton1_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global dig0
global dig1
global dig2
global dig3

dig0 = get(hObject,'Value')
tiny_send_dig(dig0, dig1, dig2, dig3)


% Hint: get(hObject,'Value') returns toggle state of togglebutton1


% --- Executes on button press in togglebutton2.
function togglebutton2_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global dig0
global dig1
global dig2
global dig3

dig1 = get(hObject,'Value')
tiny_send_dig(dig0, dig1, dig2, dig3)

% Hint: get(hObject,'Value') returns toggle state of togglebutton2


% --- Executes on button press in togglebutton3.
function togglebutton3_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global dig0
global dig1
global dig2
global dig3

dig2 = get(hObject,'Value')
tiny_send_dig(dig0, dig1, dig2, dig3)

% Hint: get(hObject,'Value') returns toggle state of togglebutton3


% --- Executes on button press in togglebutton4.
function togglebutton4_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global dig0
global dig1
global dig2
global dig3

dig3 = get(hObject,'Value')
tiny_send_dig(dig0, dig1, dig2, dig3)

% Hint: get(hObject,'Value') returns toggle state of togglebutton4


% --- Executes on selection change in popupmenu5.
function popupmenu5_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global CH1_AC
CH1_AC = get(hObject,'Value') - 1

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu5 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu5


% --- Executes during object creation, after setting all properties.
function popupmenu5_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in popupmenu6.
function popupmenu6_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global CH2_AC
CH2_AC = get(hObject,'Value') - 1
% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu6 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu6


% --- Executes during object creation, after setting all properties.
function popupmenu6_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit15_Callback(hObject, eventdata, handles)
% hObject    handle to edit15 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit15 as text
%        str2double(get(hObject,'String')) returns contents of edit15 as a double

global trigger
trigger.h = str2double(get(hObject,'String'))


% --- Executes during object creation, after setting all properties.
function edit15_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit15 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit16_Callback(hObject, eventdata, handles)
% hObject    handle to edit16 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit16 as text
%        str2double(get(hObject,'String')) returns contents of edit16 as a double
global trigger
trigger.l = str2double(get(hObject,'String'))


% --- Executes during object creation, after setting all properties.
function edit16_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit16 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in togglebutton5.
function togglebutton5_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of togglebutton5
global trigger
trigger.enabled = get(hObject,'Value')



function edit17_Callback(hObject, eventdata, handles)
% hObject    handle to edit17 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit17 as text
%        str2double(get(hObject,'String')) returns contents of edit17 as a double
global gui_awg_waveform_aux
gui_awg_waveform_aux = get(hObject,'String');


% --- Executes during object creation, after setting all properties.
function edit17_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit17 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton9.
function pushbutton9_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton9 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global gui_awg_waveform_aux
global gui_awg_amplitude_aux
global gui_awg_frequency_aux
global global_mode
global mode7_func

gui_awg_waveform_aux
gui_awg_amplitude_aux
gui_awg_frequency_aux
if(global_mode==7) & ((mode7_func=='R') | (mode7_func=='C'))
    error('I SHOULDN''T BE DOING ANYTHING IN R or C MODE (see first_gui.m)')
    return
end
tiny_send_auxwf(eval(gui_awg_waveform_aux), amp2bin(str2num(gui_awg_amplitude_aux),2), str2num(gui_awg_frequency_aux));
    fprintf('\nAux\n')


function edit18_Callback(hObject, eventdata, handles)
% hObject    handle to edit18 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit18 as text
%        str2double(get(hObject,'String')) returns contents of edit18 as a double
global gui_awg_amplitude_aux
gui_awg_amplitude_aux = get(hObject,'String');


% --- Executes during object creation, after setting all properties.
function edit18_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit18 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit19_Callback(hObject, eventdata, handles)
% hObject    handle to edit19 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit19 as text
%        str2double(get(hObject,'String')) returns contents of edit19 as a double
global gui_awg_frequency_aux
gui_awg_frequency_aux = get(hObject,'String');

% --- Executes during object creation, after setting all properties.
function edit19_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit19 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton10.
function pushbutton10_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton10 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
avrbreak;
pause;


% --- Executes on selection change in popupmenu7.
function popupmenu7_Callback(hObject, eventdata, handles)
% hObject    handle to popupmenu7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns popupmenu7 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from popupmenu7
global mode7_func

contents = cellstr(get(hObject,'String'));
mode7_func = contents{get(hObject,'Value')};
if(mode7_func=='R')
    tiny_send_auxwf(1, amp2bin(3.3, 2), 1);
end
if(mode7_func=='C')
    tiny_send_auxwf([1 0], amp2bin(3.3, 2), 10);
end

if(mode7_func~='V')
    set(handles.edit20, 'Visible', 'on')
else
    set(handles.edit20, 'Visible', 'off')
end

if(mode7_func=='C')
    set(handles.text14, 'Visible', 'on')
else
    set(handles.text14, 'Visible', 'off')
end

% --- Executes during object creation, after setting all properties.
function popupmenu7_CreateFcn(hObject, eventdata, handles)
% hObject    handle to popupmenu7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit20_Callback(hObject, eventdata, handles)
% hObject    handle to edit20 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit20 as text
%        str2double(get(hObject,'String')) returns contents of edit20 as a double
global Rtest
Rtest = str2double(get(hObject,'String'));


% --- Executes during object creation, after setting all properties.
function edit20_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit20 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in checkbox1.
function checkbox1_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox1
global scope_filter_enabled
scope_filter_enabled = get(hObject,'Value')

if(scope_filter_enabled == 1)
    set(handles.edit22, 'Visible', 'on')
else
    set(handles.edit22, 'Visible', 'off')
end



function edit22_Callback(hObject, eventdata, handles)
% hObject    handle to edit22 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit22 as text
%        str2double(get(hObject,'String')) returns contents of edit22 as a double
global scope_filter_value
scope_filter_value = str2double(get(hObject,'String'));

% --- Executes during object creation, after setting all properties.
function edit22_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit22 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pushbutton12.
function pushbutton12_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton12 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

function text17_ButtonDownFcn(hObject, eventdata, handles)
clicktype = get(handles.figure1,'selectionType');
switch (clicktype)
    case 'normal'
        disp('LEFT CLICK')
    case 'alt'
        disp('RIGHT CLICK')
    otherwise
        disp('OTHER')
end

function scroll_callback(hObject, eventdata, handles)
direction = eventdata.VerticalScrollCount

global scope_window_time

scope_window_time

if (direction == 1) && (scope_window_time<9.9)
    scope_window_time = scope_window_time * sqrt(sqrt(10));
end

if (direction == -1) && (scope_window_time>1.1e-5)
    scope_window_time = scope_window_time / sqrt(sqrt(10));
end

scope_window_time


% --- Executes on button press in checkbox4.
function checkbox4_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox4 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox4

global gui_cursor_mode
switch(gui_cursor_mode)
    case 1
        gui_cursor_mode = 3;
    case 2
        gui_cursor_mode = 4;
    case 3
        gui_cursor_mode = 1;
    case 4
        gui_cursor_mode = 2;
end

if(gui_cursor_mode>1)
    set(handles.text9, 'Visible', 'on')
else
    set(handles.text9, 'Visible', 'off')
end

% --- Executes on button press in checkbox5.
function checkbox5_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox5 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox5
global gui_cursor_mode
switch(gui_cursor_mode)
    case 1
        gui_cursor_mode = 2;
    case 2
        gui_cursor_mode = 1;
    case 3
        gui_cursor_mode = 4;
    case 4
        gui_cursor_mode = 3;
end

if(gui_cursor_mode>1)
    set(handles.text9, 'Visible', 'on')
else
    set(handles.text9, 'Visible', 'off')
end



% --- Executes on button press in checkbox6.
function checkbox6_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox6
global CH1_AC
CH1_AC = get(hObject,'Value')

% --- Executes on button press in checkbox7.
function checkbox7_Callback(hObject, eventdata, handles)
% hObject    handle to checkbox7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of checkbox7
global CH2_AC
CH2_AC = get(hObject,'Value')


% --- Executes on button press in togglebutton6.
function togglebutton6_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton6 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of togglebutton6



function edit23_Callback(hObject, eventdata, handles)
% hObject    handle to edit23 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit23 as text
%        str2double(get(hObject,'String')) returns contents of edit23 as a double
global trigger
trigger.h = str2double(get(hObject,'String'))


% --- Executes during object creation, after setting all properties.
function edit23_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit23 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function edit24_Callback(hObject, eventdata, handles)
% hObject    handle to edit24 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of edit24 as text
%        str2double(get(hObject,'String')) returns contents of edit24 as a double
global trigger
trigger.l = str2double(get(hObject,'String'))


% --- Executes during object creation, after setting all properties.
function edit24_CreateFcn(hObject, eventdata, handles)
% hObject    handle to edit24 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in togglebutton7.
function togglebutton7_Callback(hObject, eventdata, handles)
% hObject    handle to togglebutton7 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of togglebutton7
global trigger
trigger.enabled = get(hObject,'Value')


if(trigger.enabled == 1)
    set(handles.edit23, 'Visible', 'on')
    set(handles.edit24, 'Visible', 'on')
else
    set(handles.edit23, 'Visible', 'off')
    set(handles.edit24, 'Visible', 'off')
end
