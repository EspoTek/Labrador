function [bin] = amp2bin(amp, channel)

global dac_top;

global trip_state
channel = uint8(channel);
trip_state = bitand(trip_state,bitcmp(channel))

if amp>dac_top
    amp = amp/3;
    trip_state = bitor(trip_state, channel)
end

signal_trip(trip_state)
amp
bin = round(amp/dac_top*255)
