function [] = labrador_send_debug_command(usb_handle, usb_context);
  
    SIZE_OF_UNIFIED_DEBUG = 27;
        
    USB_Control_IN_data = mex_usb_send_control(usb_handle, usb_context, 'c0', 'a0', '0', '0', dec2hex(SIZE_OF_UNIFIED_DEBUG), []);
    
    USB_Control_IN_data
    
    debugtext = char(USB_Control_IN_data(1:9))  ;
    trfcnt0 = uint16(USB_Control_IN_data(10)) + 255 * uint16(USB_Control_IN_data(11));
    trfcnt1 = uint16(USB_Control_IN_data(12)) + 255 * uint16(USB_Control_IN_data(13));
    medianTrfcnt = uint16(USB_Control_IN_data(14)) + 255 * uint16(USB_Control_IN_data(15));
    outOfRange = uint16(USB_Control_IN_data(16)) + 255 * uint16(USB_Control_IN_data(17));
    counter = uint16(USB_Control_IN_data(18)) + 255 * uint16(USB_Control_IN_data(19));
    dma_ch0_cnt = uint16(USB_Control_IN_data(20)) + 255 * uint16(USB_Control_IN_data(21));
    dma_ch1_cnt = uint16(USB_Control_IN_data(22)) + 255 * uint16(USB_Control_IN_data(23));

    fprintf("debugtext = %s\ntrfcnt0 = %d\ntrfcnt1 = %d\nmedianTrfcnt = %d\noutOfRange = %d\ncounter = %d\ndma_ch0_cnt = %d\ndma_ch1_cnt = %d\n",debugtext, trfcnt0, trfcnt1, medianTrfcnt, outOfRange, counter, dma_ch0_cnt, dma_ch1_cnt);
