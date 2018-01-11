clc

fprintf("\n\n\nCompiling USB_INIT_LIBUSB...\n\n\n");
fflush(stdout);
mex C/USB_INIT_LIBUSB.c -IC/build_linux/libusb -lusb-1.0 -Lbin\lib\x64 
copyfile USB_INIT_LIBUSB.mex C/mex_outputs
copyfile USB_INIT_LIBUSB.o C/mex_outputs
delete USB_INIT_LIBUSB.mex
delete USB_INIT_LIBUSB.o


fprintf("\n\n\nCompiling USB_EXIT_LIBUSB...\n\n\n");
fflush(stdout);
mex C/USB_EXIT_LIBUSB.c -IC/build_linux/libusb -lusb-1.0 -Lbin\lib\x64 
copyfile USB_EXIT_LIBUSB.mex C/mex_outputs
copyfile USB_EXIT_LIBUSB.o C/mex_outputs
delete USB_EXIT_LIBUSB.mex
delete USB_EXIT_LIBUSB.o

fprintf("\n\n\nCompiling USB_CONTROL_SEND_LIBUSB...\n\n\n");
fflush(stdout);
mex C/USB_CONTROL_SEND_LIBUSB.c -IC/build_linux/libusb -lusb-1.0 -Lbin\lib\x64 
copyfile USB_CONTROL_SEND_LIBUSB.mex C/mex_outputs
copyfile USB_CONTROL_SEND_LIBUSB.o C/mex_outputs
delete USB_CONTROL_SEND_LIBUSB.mex
delete USB_CONTROL_SEND_LIBUSB.o


%mex USB_ISO_INIT.c -Iincludes -lusb-1.0
%mex USB_ISO_LOOP.c -Iincludes -lusb-1.0
%mex USB_POOL_FREE.c -Iincludes -lusb-1.0

