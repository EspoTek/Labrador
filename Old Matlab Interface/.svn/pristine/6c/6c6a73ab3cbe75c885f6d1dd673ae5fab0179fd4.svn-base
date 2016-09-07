function [OUT] = mex_usb_send_control( RequestType, Request, Value, Index, Length, LDATA)

global usb_handle
if ~length(usb_handle)
    warning('USB Handle not initialised.  Initialising!')
    mex_usb_init('03eb', 'a000')
end
OUT = USB_CTRL_SEND(usb_handle, RequestType, Request, Value, Index, Length, LDATA);