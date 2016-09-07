function [] = setpsu_boost(vo)
%     err = verr(vo, r)
%     D = 1 - vi/(vo+err)
%     if D>0.75
%         error('PSU DUTY CYCLE TOO LARGE!!!  ABORTING!!!')
%     end
%     D = uint16(D*255)
    D = expected_adc(vo)
    if D>113 | D<21
        error('PSU DUTY CYCLE TOO LARGE (could underflow on SOF)!!!  ABORTING!!!')
    end
    mex_usb_send_control('40', 'a3', dec2hex(D), '0', '0', '0');
