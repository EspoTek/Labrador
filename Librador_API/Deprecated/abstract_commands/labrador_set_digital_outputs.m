function [] = labrador_set_digital_outputs(usb_handle, usb_context, port0, port1, port2, port3);
    digital_state = uint16(0);
    
    if(port0 ~= 0) digital_state = digital_state + 1; end
    if(port1 ~= 0) digital_state = digital_state + 2; end
    if(port2 ~= 0) digital_state = digital_state + 4; end
    if(port3 ~= 0) digital_state = digital_state + 8; end
        
    mex_usb_send_control(usb_handle, usb_context, '40', 'a6', dec2hex(digital_state), '0', '0', []);