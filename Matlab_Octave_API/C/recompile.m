clc

fprintf("\n\n\nCompiling Thread_Example...\n\n\n");
fflush(stdout);
mex C/Thread_Example.c -IC/build_linux/libusb -lusb-1.0 -Lbin\lib\x64 -O0
copyfile Thread_Example.mex C/mex_outputs
copyfile Thread_Example.o C/mex_outputs
delete Thread_Example.mex
delete Thread_Example.o

fprintf("\n\n\nCompiling USB_INIT_LIBUSB...\n\n\n");
fflush(stdout);
mex C/USB_INIT_LIBUSB.c -IC/build_linux/libusb -lusb-1.0 -Lbin\lib\x64 -O0
copyfile USB_INIT_LIBUSB.mex C/mex_outputs
copyfile USB_INIT_LIBUSB.o C/mex_outputs
delete USB_INIT_LIBUSB.mex
delete USB_INIT_LIBUSB.o


fprintf("\n\n\nCompiling USB_EXIT_LIBUSB...\n\n\n");
fflush(stdout);
mex C/USB_EXIT_LIBUSB.c -IC/build_linux/libusb -lusb-1.0 -Lbin\lib\x64 -O0
copyfile USB_EXIT_LIBUSB.mex C/mex_outputs
copyfile USB_EXIT_LIBUSB.o C/mex_outputs
delete USB_EXIT_LIBUSB.mex
delete USB_EXIT_LIBUSB.o

fprintf("\n\n\nCompiling USB_CONTROL_SEND_LIBUSB...\n\n\n");
fflush(stdout);
mex C/USB_CONTROL_SEND_LIBUSB.c -IC/build_linux/libusb -lusb-1.0 -Lbin\lib\x64 -O0
copyfile USB_CONTROL_SEND_LIBUSB.mex C/mex_outputs
copyfile USB_CONTROL_SEND_LIBUSB.o C/mex_outputs
delete USB_CONTROL_SEND_LIBUSB.mex
delete USB_CONTROL_SEND_LIBUSB.o

fprintf("\n\n\nCompiling USB_ISO_INIT_LIBUSB...\n\n\n");
fflush(stdout);
mex C/USB_ISO_INIT_LIBUSB.c -IC/build_linux/libusb -lusb-1.0 -Lbin\lib\x64 -O0
copyfile USB_ISO_INIT_LIBUSB.mex C/mex_outputs
copyfile USB_ISO_INIT_LIBUSB.o C/mex_outputs
delete USB_ISO_INIT_LIBUSB.mex
delete USB_ISO_INIT_LIBUSB.o

%mex USB_ISO_LOOP.c -Iincludes -lusb-1.0
%mex USB_POOL_FREE.c -Iincludes -lusb-1.0

