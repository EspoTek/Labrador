a = 1:100
b = 101:200

for k = 1:100
    plot(1,1)
end
tic
hold on
    plot(a,b)
    stairs(a,b)
toc