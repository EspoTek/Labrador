clear all
temp_waveform = false(1,500);

dig_samples = uint8([0:32]);
%%, 0:255, 0:255, 0:255

tic
if (length(dig_samples)>500)
    temp_samples = dig_samples(1:length(dig_samples)/500:end);
    temp_waveform = logical(bitand(temp_samples,16));
else
    temp_samples = false(1,length(dig_samples)*8);
    temp_samples(1:8:length(temp_samples)) = bitand(dig_samples,1);
    temp_samples(2:8:length(temp_samples)) = bitand(dig_samples,2);
    temp_samples(3:8:length(temp_samples)) = bitand(dig_samples,4);
    temp_samples(4:8:length(temp_samples)) = bitand(dig_samples,8);
    temp_samples(5:8:length(temp_samples)) = bitand(dig_samples,16);
    temp_samples(6:8:length(temp_samples)) = bitand(dig_samples,32);
    temp_samples(7:8:length(temp_samples)) = bitand(dig_samples,64);
    temp_samples(8:8:length(temp_samples)) = bitand(dig_samples,128);
    
    temp_waveform = temp_samples(1:length(temp_samples)/500:end);
end
toc

stairs(temp_waveform);
%b = [bitand(a,128), bitand(a,64), bitand(a,32), bitand(a,16), bitand(a,8), bitand(a,4), bitand(a,2), bitand(a,1)];
%b(logical(mod(1:500,2))) = true;

