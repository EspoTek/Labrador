function [USB_Control_IN_data] = mex_usb_send_control(usb_handle, usb_context, RequestType, Request, Value, Index, Length, LDATA) 

[USB_Control_IN_data] = USB_CONTROL_SEND_LIBUSB(usb_handle, usb_context, RequestType, Request, Value, Index, Length, LDATA);