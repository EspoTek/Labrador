clear all
clc
vex = [5 8 10 12 15];

v68 = vex - [4.4 6.75 8.05 9.12 10.29];
v220 = vex - [4.53 7.14 8.74 10.11 11.97];
vinf = vex - [4.59 8.40 9.92 10.82 12.98];

r68 = (1/68 + 1/250)^-1;
r220 = (1/220 + 1/250)^-1;
rinf = 250;

magic = 1.5;
mag_exponent = 4;

c68 = mean(v68./((vex+magic).^mag_exponent));
c220 = mean(v220./((vex+magic).^mag_exponent));
cinf = mean(vinf./((vex+magic).^mag_exponent));

c68*r68
c220*r220
cinf*rinf