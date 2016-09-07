function [] = signal_trip(toggle)

if toggle ~= 0 && toggle~= 1 && toggle~=2 && toggle~=3
    error('INVALID SIGNAL_TRIP INPUT')
end

mex_usb_send_control('40', 'a4', dec2hex(toggle), '0', '0', '0');
