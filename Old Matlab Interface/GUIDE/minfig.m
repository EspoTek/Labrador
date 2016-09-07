%MINFIG   Minimize a figure
%   MINFIG(F,1) minimizes the figure window for the figure with handle F
%   MINFIG(F,0) restores figure F if F is minimized
%
%   Example:
%   If
%       f = figure;
%       surf(peaks);
%   then
%       minfig(f,1)     minimizes the figure
% 
%   See also MAXFIG, FIGSTATE