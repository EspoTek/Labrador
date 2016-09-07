%MAXFIG   Maximize a figure
%   MAXFIG(F,1) maximizes the figure window for the figure with handle F
%   MAXFIG(F,0) restores figure F if F is maximized
%
%   Example:
%   If
%       f = figure;
%       surf(peaks)
%   then
%       maxfig(f,1)     maximizes the figure
% 
%   See also MINFIG, FIGSTATE