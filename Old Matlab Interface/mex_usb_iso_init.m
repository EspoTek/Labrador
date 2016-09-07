clear all

compile

global usb_handle
if ~length(usb_handle)
    warning('USB Handle not initialised.  Initialising!')
    mex_usb_init('03eb', 'a000')
end

%mex USB_ISO_INIT.c -Iincludes -llibusbK -Lbin\lib\amd64
%USB_ISO_INIT(usb_handle)
[stm_handle] = USB_ISO_INIT(usb_handle)
%USB_ISO_LOOP(usb_handle, isoCtx, ovlkHandle, ovlPool, isoBuffer, uint8(0))