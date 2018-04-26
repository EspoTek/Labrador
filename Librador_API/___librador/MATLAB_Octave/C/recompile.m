clc

fprintf("\n\n\nCompiling Thread_Example...\n\n\n");
fflush(stdout);
mex C/mexsrc/Thread_Example.c -I../../../Desktop_Interface/build_linux/libusb -lusb-1.0 -Lbin\lib\x64 -DCOMPILE_FOR_OCTAVE
fprintf("Moving Thread_Example...\n");
copyfile Thread_Example.mex C/mex_outputs;
copyfile Thread_Example.o C/mex_outputs;
delete Thread_Example.mex;
delete Thread_Example.o;

librador_compile('matlab_octave_api_librador_init', 'OCTAVE')