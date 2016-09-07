function [err] = verr(vex, r)

if r<50
    error('R IS TOO LOW!!!')
end

%%FOR THE BIG BOY BOARD, remove the +0.2 also
%r = (1/r + 1/250)^-1;
err = ((vex + 1.5)^4 / (80 * r)) + 0.2

%err = vex^3/512 - (r/68) * (vex^1.8/(20^1.8)) - (vex-10) / 10 +vex/20