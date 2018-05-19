function [retVal] = librador_update_signal_gen_settings(channel, samples, usecs_between_samples, amplitude_v, offset_v)
  sampleBuffer = samples
  numSamples = length(sampleBuffer)
  retVal = matlab_octave_api_librador_update_signal_gen_settings(channel, sampleBuffer, numSamples, usecs_between_samples, amplitude_v, offset_v);