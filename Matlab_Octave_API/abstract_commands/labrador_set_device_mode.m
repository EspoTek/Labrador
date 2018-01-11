function [] = labrador_set_device_mode(usb_handle, usb_context, device_mode, oscilloscope_gain);
  
    if(device_mode~=0 && device_mode~=1 && device_mode~=2 && device_mode~=3 && device_mode~=4 && device_mode~=6 && device_mode~=7)
      error_message = sprintf('\nInvalid Device Mode\nValid device modes are:\n0 - Oscilloscope CH1 only\n1 - Oscilloscope CH1 and Logic Analyzer CH1\n2 - Oscillscope CH1 and CH2\n3 - Logic Analyzer CH1 only\n4 - Logic Analzyer CH1 and CH2\n6 - Oscilloscope CH1 in 750ksps mode\n7 - Multimeter\nNote that mode 5 is intentionally left invalid.\n');
      error(error_message);
    end
  
    if(oscilloscope_gain~=0.5 && oscilloscope_gain~=1 && oscilloscope_gain~=2 && oscilloscope_gain~=4 && oscilloscope_gain~=8 && oscilloscope_gain~=16 && oscilloscope_gain~=32 && oscilloscope_gain~=64)
        error_message = sprintf('Cannot set the oscilloscope gain to any values apart from 0.5, 1, 2, 4, 8, 16, 32 or 64\nAborting...\n');
        error(error_message);
    end
    if (oscilloscope_gain == 1/2)
        gain_mask = 7;
    else 
        gain_mask = log2(oscilloscope_gain);
    end
    
    mex_usb_send_control(usb_handle, usb_context, '40', 'a5', dec2hex(device_mode), dec2hex(gain_mask), '0', []);
