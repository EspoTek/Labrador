% Copyright (C) 2018 Christopher Paul Esposito
%
% This program is free software: you can redistribute it and/or modify
% it under the terms of the GNU General Public License as published by
% the Free Software Foundation, either version 3 of the License, or
% (at your option) any later version.
%
% This program is distributed in the hope that it will be useful,
% but WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% GNU General Public License for more details.
%
% You should have received a copy of the GNU General Public License
% along with this program.  If not, see <http://www.gnu.org/licenses/>.

function [outputArray] = librador_get_analog_data(channel, timeWindow_seconds, sampleRate_hz, delay_seconds, filter_mode)

    if(mod(channel, 1)~=0)
        error('Value of channel must be a whole number');
    end

    if(mod(filter_mode, 1)~=0)
        error('Value of filter_mode must be a whole number');
    end

    if(~isa(sampleRate_hz, 'double'))
        error('sampleRate_hz must be of type double.\n(non-programmers, this means a real, numeric value stored in double precision.  Type ''help double'' in the console for more info.)');
    end

    if(~isa(delay_seconds, 'double'))
        error('delay_seconds must be of type double.\n(non-programmers, this means a real, numeric value stored in double precision.  Type ''help double'' in the console for more info.)');
    end

    if(~isa(timeWindow_seconds, 'double'))
        error('timeWindow_seconds must be of type double.\n(non-programmers, this means a real, numeric value stored in double precision.  Type ''help double'' in the console for more info.)');
    end

    outputArray = matlab_octave_api_librador_get_analog_data(channel, timeWindow_seconds, sampleRate_hz, delay_seconds, filter_mode);
