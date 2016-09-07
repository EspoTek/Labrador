function [] = printusb(inputstring);
if length(inputstring)>21
    error('String too long.  Reduce to under 21 chars.')
end

normalisedString='                     ';
normalisedString(1:length(inputstring)) = inputstring;

driverLocation = 'c:\libusbk\examples\open-device\debug\win32';
command = [driverLocation '\open-device "' normalisedString '" "1" "03eb" "a000"']
system(command);