function [usb_context, usb_handle]  = mex_usb_init(VID, PID) 

[usb_handle, usb_context] = USB_INIT_LIBUSB(VID, PID);