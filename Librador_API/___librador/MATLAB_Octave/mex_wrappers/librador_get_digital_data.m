function [outputArray] = librador_get_digital_data(channel, timeWindow_seconds, sampleRate_hz, delay_seconds)
    
outputArray = matlab_octave_api_librador_get_digital_data(channel, timeWindow_seconds, sampleRate_hz, delay_seconds);
