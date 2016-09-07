function [] = mex_usb_init(VID, PID) 

global usb_handle

usb_handle = USB_INIT(VID, PID);