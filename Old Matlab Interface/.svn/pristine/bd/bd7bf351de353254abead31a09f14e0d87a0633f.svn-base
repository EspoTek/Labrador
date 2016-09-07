function [] = setpsu(vo, ro);

vcc = 3.3;
gain = 4.22;
vdrop = 0;
PER=256;

psucal
vdrop = polyval(p_oc, vo) + polyval(p_ios,vo) - vo;

CCA = ((vo + vdrop)*PER)/(vcc*gain);
CCA = uint16(CCA)

mex_usb_send_control('40', 'a3', dec2hex(CCA), '0', '0', '0');

% driverLocation = 'c:\libusbk\examples\open-device\debug\win32';
% command = [driverLocation '\open-device "03eb" "a000" "' command '" "' num2str(CCA) '" "NULL" "NULL" "NULL"']
% system(command);