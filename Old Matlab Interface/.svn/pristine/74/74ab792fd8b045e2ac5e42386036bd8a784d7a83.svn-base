function [] = setscopewindowsize(time,vmin,vmax)
global scope_window_time
global scope_window_min
global scope_window_max

if (vmax<vmin)
    warning('Vmax is les than Vmin.  Swapping the values around...')
    temp = vmax;
    vmax = vmin;
    vmin = temp;
end
    
scope_window_time = time;
scope_window_min = vmin;
scope_window_max = vmax;

