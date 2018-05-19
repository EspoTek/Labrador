clear all
clc

__addpaths

%Standard device initialisation
librador_init()
ibrador_setup_usb()

%Simple test call.  Should show values that include a counter ~= 12000.
librador_avr_debug()

%Send a 5Hz sine wave with vpp of 2V and a minimum voltage of 1V (ie, DC offset of 2V in the Fourier sense).
librador_send_sin_wave(1, 5, 2, 1)

%Set the gain to something more reasonable.  This is good for +-3V or so.
librador_set_oscilloscope_gain(4)

%Set device to mode 2.  Oscilloscope CH1 and CH2 active.
librador_set_device_mode(2)

%Get some sample data from the oscilloscope and plot it.
pause(1);
CH1 = librador_get_analog_data(1, 1, 375000, 0.1, 0);
CH2 = librador_get_analog_data(2, 1, 375000, 0.1, 0);
plot(1:length(CH1), CH1, 1:length(CH1), CH2);

%Wait for keypress to continue.
pause()

%Change device to mode 3, digtial CH1 only
librador_set_device_mode(3)

%Get some digital data and plot it
pause(1)
CH1 = librador_get_digital_data(1, 1, 375000, 0.1);
plot(CH1)

%Close the API
librador_exit()