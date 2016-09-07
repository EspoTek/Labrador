function [cool_waveform] = undofrontend(temp_waveform,channel)

Vcc = 3.3;
vref = Vcc/2;
TOP = 128;
R4 = 75e3;
R3 = 1e6;
R2 = 1e3;
R1 = 1e3;

global scope_gain_0
global scope_gain_1
global CH1_AC
global CH2_AC
global scope_mode
global mode7_func
global Rtest
global scope_filter_value
global scope_filter_enabled

if channel == 1
    scope_gain = scope_gain_1
    AC_offset = CH2_AC * 1.65
else
    scope_gain = scope_gain_0
    AC_offset = CH1_AC * 1.65
end

cool_waveform = double(temp_waveform);

if scope_mode==7
    TOP = 2048;  %%OVERRIDE DEFAULTS!!
    switch(scope_gain)
        case 0.5
            offset = -0.27;
        case 1
            offset = 0;
        case 2
            offset = 0.037;
        case 4
            offset = 0.053;
        case 8
            offset = 0.055;
        case 16
            offset = 0.028;
        case 32
            offset= 0.035;
        case 64
            offset = 0.0355
        otherwise
            error('UNDOFRONTEND failed')
    end
    switch(mode7_func)
        case 'V'
            cool_waveform = (cool_waveform * (Vcc/2)) / (R4/(R3+R4)*scope_gain*TOP);
            cool_waveform = cool_waveform - AC_offset;
            cool_waveform = cool_waveform - offset;
        case 'I'
            cool_waveform = (cool_waveform * (Vcc/2)) / (R4/(R3+R4)*scope_gain*TOP);
            cool_waveform = cool_waveform - AC_offset;
            cool_waveform = cool_waveform - offset;
            cool_waveform = cool_waveform/Rtest
        case 'R'
            cool_waveform = (cool_waveform * (Vcc/2)) / (R4/(R3+R4)*scope_gain*TOP);
            cool_waveform = cool_waveform - AC_offset;
            cool_waveform = cool_waveform - offset;
            cool_waveform = (cool_waveform * Rtest) ./  ((Vcc/2) - cool_waveform);
        case 'C'
            cool_waveform = (cool_waveform * (Vcc/2)) / (R4/(R3+R4)*scope_gain*TOP);
            cool_waveform = cool_waveform - AC_offset;
            cool_waveform = cool_waveform - offset;
            

            %Capacitance calculation
            tt = 2.5;
            bt = 0.8;

            top_val = (tt/vref * R4/(R3+R4) *  scope_gain * TOP)
            bot_val = (bt/vref * R4/(R3+R4) *  scope_gain * TOP)
            
            global saved_waveform_ch1
            global fastmode
            samples_per_sec = 375000 / (3 * fastmode + 1)
            range = length(saved_waveform_ch1) - samples_per_sec / 5

            gtt = saved_waveform_ch1(range:end)>top_val;
            gtb = saved_waveform_ch1(range:end)<bot_val;

            num_samples = 50
            first_bip = find(gtb,num_samples);
            if ~isempty(first_bip)
                first_bip = first_bip(end);

                second_bip = find(~gtb(first_bip:end), num_samples);
                if ~isempty(second_bip)
                    second_bip = second_bip(end) + first_bip;

                    third_bip = find(gtt(second_bip:end), num_samples);
                    if ~isempty(third_bip)
                        third_bip = third_bip(end) + second_bip;

                        samples_per_sec = 375000 / (3 * fastmode + 1);
                        dt = (third_bip - second_bip) / samples_per_sec;

                        C_measured = -dt / (Rtest * log((Vcc-tt)/(Vcc-bt)))
                        global text_box_c
                        set(text_box_c, 'String', sprintf('C = %.3enF', C_measured * 1e9));
                    end
                end
            end
            
            
        case 'L'
            cool_waveform = (cool_waveform * (Vcc/2)) / (R4/(R3+R4)*scope_gain*TOP);
            cool_waveform = cool_waveform - AC_offset;
            cool_waveform = cool_waveform - offset;
        otherwise
            error('UNDOFRONTEND FAILED')
    end
else
    cool_waveform = (cool_waveform * (Vcc/2)) / (R4/(R3+R4)*scope_gain*TOP) + Vcc*(R2/(R1+R2));
    cool_waveform = cool_waveform - AC_offset;
end
if(scope_filter_enabled)
    if scope_filter_value>0
        cool_waveform = filter(ones(1,scope_filter_value)/scope_filter_value,1,cool_waveform);
        cool_waveform = cool_waveform(scope_filter_value:end);
    end
end