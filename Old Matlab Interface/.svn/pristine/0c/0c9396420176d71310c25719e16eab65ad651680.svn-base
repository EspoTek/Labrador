function [isoLog] = plotiso(mode)

iso_incoming;

load('isoLog.txt');
window = 750;
switch (mode)
    case 1
    for n=1:32:((length(isoLog))-window)
        plot(isoLog(n:n+window));
        drawnow
        pause(0.03);
    end
    otherwise
        plot(isoLog);
end

