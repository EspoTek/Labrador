function [retVal] = librador_send_triangle_wave(channel, frequency_hz, amplitude_v, offset_v)
  retVal = matlab_octave_api_librador_send_triangle_wave(channel, frequency_hz, amplitude_v, offset_v);