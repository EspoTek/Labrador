clear all
clc

__addpaths;
__load_globals;

[usb_handle, usb_context] = mex_usb_init("03eb", "ba94");
if(isequal(usb_handle, "0000000000000000"))
  fprintf("Null USB Handle!  Cancelling...\n");
  return;
end

fprintf("\nTurning on the digital outputs...\n");
fflush(stdout);
labrador_set_digital_outputs(usb_handle, usb_context, 1,1,1,1);


fprintf("\nSetting PSU to 8.8V...\n");
fflush(stdout);
labrador_set_psu_voltage(usb_handle, usb_context, 8.8);

%pause(2)
%fprintf("\nTurning off the digital outputs...\n");
%fflush(stdout);
%labrador_set_digital_outputs(usb_handle, usb_context, 0,0,0,0);


fprintf("\nExiting Libusb...\n");
fflush(stdout);
mex_usb_exit(usb_handle, usb_context);
  