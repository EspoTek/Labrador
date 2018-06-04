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
librador_compile('matlab_octave_api_librador_exit', 'OCTAVE')
librador_compile('matlab_octave_api_librador_setup_usb', 'OCTAVE')
librador_compile('matlab_octave_api_librador_avr_debug', 'OCTAVE')
librador_compile('matlab_octave_api_librador_update_signal_gen_settings', 'OCTAVE')
librador_compile('matlab_octave_api_librador_send_sin_wave', 'OCTAVE')
librador_compile('matlab_octave_api_librador_send_square_wave', 'OCTAVE')
librador_compile('matlab_octave_api_librador_send_triangle_wave', 'OCTAVE')
librador_compile('matlab_octave_api_librador_send_sawtooth_wave', 'OCTAVE')
librador_compile('matlab_octave_api_librador_set_power_supply_voltage', 'OCTAVE')
librador_compile('matlab_octave_api_librador_set_device_mode', 'OCTAVE')
librador_compile('matlab_octave_api_librador_set_oscilloscope_gain', 'OCTAVE')
librador_compile('matlab_octave_api_librador_set_digital_out', 'OCTAVE')
librador_compile('matlab_octave_api_librador_reset_device', 'OCTAVE')
librador_compile('matlab_octave_api_librador_jump_to_bootloader', 'OCTAVE')
librador_compile('matlab_octave_api_librador_get_device_firmware_version', 'OCTAVE')
librador_compile('matlab_octave_api_librador_get_device_firmware_variant', 'OCTAVE')
librador_compile('matlab_octave_api_librador_get_analog_data', 'OCTAVE')
librador_compile('matlab_octave_api_librador_get_analog_data_sincelast', 'OCTAVE')
librador_compile('matlab_octave_api_librador_get_digital_data', 'OCTAVE')