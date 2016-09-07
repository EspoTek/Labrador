%vdrop = 0

% for in = 1:10
%     setpsu(in)
%     pause(5)
% end

% clear all
% clc
% 
% ro=22;

vout22 = [0.38 1.32 2.26  3.25 4.19 5.12 6.12 7.05 7.93 8.94];
iout22 = vout22/22;

vout220 = [0.36 1.32 2.25 3.24 4.18 5.12 6.12 7.05 8.00 8.99];

vout_oc = [0.41 1.37 2.30 3.29 4.23 5.17 6.16 7.10 8.04 9.04];

p_oc = polyfit(vout_oc, 1:10, 1);
polyval(p_oc, 1:10);

vos_22 = vout_oc - vout22;
p_ios = polyfit(1:10, (22/ro) * vos_22, 1);
polyval(p_ios, 1:10);
