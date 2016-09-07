clc
tic
%separate
transfer_contents_1 = double(transfer_contents_1);
topbytes = transfer_contents_1(~logical(mod(1:length(transfer_contents_0),2)));
botbytes = transfer_contents_1(logical(mod(1:length(transfer_contents_0),2)));

botbytes = sign(topbytes) .* abs(botbytes); %lower bytes should steal sign info from top byte

realval = topbytes*16 + botbytes/16; 

%%Plot
Vcc = 3.3;
TOP = 2048;
R4 = 75e3;
R3 = 1e6;
R2 = 1e3;
R1 = 1e3;
%%%%%ASUMPTION%%%%%%%%
scope_gain = 2;
%%%%%%%%%%%%%%%%%%%%%%

realval = (realval * (Vcc/2)) / (R4/(R3+R4)*scope_gain*TOP);
toc

plot(realval)