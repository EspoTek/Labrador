vref = 3.3/2;
R4 = 75e3;
R3 = 1e6;
scope_gain = 4;
TOP = 2048;
global saved_waveform_ch1;
global fastmode

tt = 2.5;
bt = 0.8;
vcc = 3.3;

tic
top_val = (tt/vref * R4/(R3+R4) *  scope_gain * TOP)
bot_val = (bt/vref * R4/(R3+R4) *  scope_gain * TOP)

samples_per_sec = 375000 / (3 * fastmode + 1)
range = length(saved_waveform_ch1) - samples_per_sec / 5


gtt = saved_waveform_ch1(range:end)>top_val;
gtb = saved_waveform_ch1(range:end)<bot_val;

num_samples = 50;

first_bip = find(gtb,num_samples);
first_bip = first_bip(end)

second_bip = find(~gtb(first_bip:end), num_samples);
second_bip = second_bip(end) + first_bip

third_bip = find(gtt(second_bip:end), num_samples);
third_bip = third_bip(end) + second_bip

dt = (third_bip - second_bip) / samples_per_sec

R_test = 100000

C_measured = -dt / (R_test * log((vcc-tt)/(vcc-bt)))


toc


%             num_samples = 20
%             first_bip = find(gtt,num_samples);
%             if ~isempty(first_bip)
%                 first_bip = first_bip(end);
% 
%                 second_bip = find(~gtt(first_bip:end), num_samples);
%                 if ~isempty(second_bip)
%                     second_bip = second_bip(end) + first_bip;
% 
%                     third_bip = find(gtb(second_bip:end), num_samples);
%                     if ~isempty(third_bip)
%                         third_bip = third_bip(end) + second_bip;
% 
%                         samples_per_sec = 375000 / (3 * fastmode + 1);
%                         dt = (third_bip - second_bip) / samples_per_sec;
% 
%                         C_measured = -dt / (Rtest * log(1/2.5)) 
%                         global text_box_c
%                         set(text_box_c, 'String', sprintf('C = %.3enF', C_measured * 1e9));
%                     end
%                 end
%             end
