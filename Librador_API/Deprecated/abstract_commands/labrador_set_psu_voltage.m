function [] = labrador_set_psu_voltage(usb_handle, usb_context, voltage);
  
    global vref;
    global PSU_ADC_TOP;

    vinp = voltage/11;
    vinn = 0;

    psu_duty_cycle = uint16(((vinp - vinn)/vref * PSU_ADC_TOP));
    
    if ((psu_duty_cycle>106) || (psu_duty_cycle<21))
        error_message = sprintf("PSU DUTY CYCLE of value %d OUT OF RANGE!\nDid you try and set the voltage below 4.5 or above 12?\nAborting...\n", psu_duty_cycle);
        error(error_message);
    end
    mex_usb_send_control(usb_handle, usb_context, '40', 'a3', dec2hex(psu_duty_cycle), '0', '0', []);
