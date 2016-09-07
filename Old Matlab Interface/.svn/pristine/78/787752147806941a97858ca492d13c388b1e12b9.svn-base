function [expected] = dofrontend(vin, channel)

vcc = 3.3;
TOP = 128;
r4 = 75e3;
r3 = 1e6;
r2 = 1e3;
r1 = 1e3;

global scope_gain_0
global scope_gain_1
global CH1_AC
global CH2_AC

if channel == 1
    scope_gain = scope_gain_1;
    AC_offset = CH2_AC * 1.65;
else
    scope_gain = scope_gain_0;
    AC_offset = CH1_AC * 1.65;
end

vn = vcc * (r2/(r1+r2));
vx = vn + (vin - vn) * (r4 / (r3+r4));
vref = vcc/2;

expected = int8((vx - vn)/vref * scope_gain * TOP);