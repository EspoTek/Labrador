function [retVal] = librador_get_device_firmware_version()
    retVal = dec2hex(matlab_octave_api_librador_get_device_firmware_version());