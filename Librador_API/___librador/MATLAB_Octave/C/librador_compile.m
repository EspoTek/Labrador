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

function [] = librador_compile(fname_no_dot_cpp, idename)
  fprintf("\n\n\nCompiling %s.cpp...\n\n\n", fname_no_dot_cpp);
  fflush(stdout);
  mex(['-DCOMPILE_FOR_' idename], '-I../../../Desktop_Interface/build_linux/libusb', '-I../librador_shared_library', '-lrador', '-L../librador_shared_library', '-Wl,-rpath=../librador_shared_library', ['C/mexsrc/' fname_no_dot_cpp '.cpp'])
  copyfile([fname_no_dot_cpp '.mex'], 'C/mex_outputs')
  delete([fname_no_dot_cpp '.mex'])
  copyfile([fname_no_dot_cpp '.o'], 'C/mex_outputs')
  delete([fname_no_dot_cpp '.o'])
return;