%clear all
fflush(stdout);
clc

#https://docs.google.com/document/d/1ZDO1RTarQTNB6Pdfi_T4YukL51oYan_kk_teb1cu6-o/edit?usp=sharing

__addpaths;
__load_globals;
fflush(stdout);

fprintf("\nInitialising USB...\n");
[usb_handle, usb_context] = mex_usb_init("03eb", "ba94");

if(isequal(usb_handle, "0000000000000000"))
  fprintf("Null USB Handle!  Cancelling...\n");
  return;
end

return;

fprintf("\nInitialising USB ISO...\n");
fflush(stdout)
mex_usb_iso_init(usb_handle, usb_context, '81');
fflush(stdout)

fprintf("\nSending AVR Debug Command...\n");
fflush(stdout);
labrador_send_debug_command(usb_handle, usb_context);

fprintf("\nSetting Device Mode to 2 (Scope CH1 and CH2) with gain 8...\n");
fflush(stdout);
labrador_set_device_mode(usb_handle, usb_context, 2, 8);


fprintf("\nTurning on the digital outputs...\n");
fflush(stdout);
labrador_set_digital_outputs(usb_handle, usb_context, 1,1,1,1);


fprintf("\nSetting PSU to 6.6V...\n");
fflush(stdout);
labrador_set_psu_voltage(usb_handle, usb_context, 6.6);

%pause(2)
%fprintf("\nTurning off the digital outputs...\n");
%fflush(stdout);
%labrador_set_digital_outputs(usb_handle, usb_context, 0,0,0,0);


fprintf("\nExiting Libusb...\n");
fflush(stdout);
mex_usb_exit(usb_handle, usb_context);
