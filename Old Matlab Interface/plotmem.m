fid = fopen('C:\users\esposch\documents\output.hex');

buffer = 0;

hexarray = [];

while (buffer ~= -1)
    buffer = fgetl(fid);
    hexarray = [hexarray buffer(10:end-2)];
end

uintarray = [];

for n=1:2:length(hexarray)
    uintarray = [uintarray hex2dec(hexarray([n n+1]))];
end

typecast(uintarray, 'int8')
plot(uintarray);

fclose(fid);