function [usb_context, usb_handle]  = mex_usb_init(VID, PID) 

[usb_context, usb_handle] = USB_INIT_LIBUSB(VID, PID);