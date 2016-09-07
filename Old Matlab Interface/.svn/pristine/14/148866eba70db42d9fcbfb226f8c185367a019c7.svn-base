function [] = lcdtoggle(onoff);

mex_usb_send_control('40', 'a1', dec2hex(onoff), '0', '0', '0');

% driverLocation = 'c:\libusbk\examples\open-device\debug\win32';
% command = [driverLocation '\open-device "03eb" "a000" "' command '" "' num2str(onoff) '" "NULL" "NULL" "NULL"']
% system(command);