function [offset] = hexoffset(hexin)
    decin = hex2dec(hexin);
    offset = dec2hex(decin+750);