x = linspace(0, 2*pi, 512)
y = 127 * sin(x) + 128
y = uint8(y)

for i = 1:512
    fprintf('%d\t', y(i));
end