function [] = tiny_send_dig(dig1, dig2, dig3, dig4)

bitmask = dig1 * 8 + dig2 * 4 + dig3 * 2 + dig4;


mex_usb_send_control('40', 'a6', dec2hex(bitmask), '0', '0', '0');
