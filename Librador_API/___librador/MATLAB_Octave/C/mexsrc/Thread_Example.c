/* Copyright (C) 2018 Christopher Paul Esposito

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//MATLAB INCLUDES

#ifdef COMPILE_FOR_OCTAVE
  #define USING_OCTAVE 1
#elif defined COMPILE_FOR_MATLAB
  #define USING_OCTAVE 0
#else
    #error "IDE not defined.  Please add -DCOMPILE_FOR_MATLAB to your mex call if you use MATLAB, or -DCOMPILE_FOR_OCTAVE if using GNU Octave."
#endif

#if !USING_OCTAVE
  #include <matrix.h>
#endif
#include <mex.h>

//LIBUSB INCLUDES
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "libusb.h"

//MISC INCLUDES
#include <math.h>
#include <string.h>
#include <unistd.h>

//https://undocumentedmatlab.com/blog/explicit-multi-threading-in-matlab-part3
//Yair, you're a genius.

void *thread_run(void *p)
{
    while(1){
        mexPrintf("Thread Running\n");
        usleep(1000000);
    }
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    pthread_t thread;

      if (pthread_create(&thread, NULL, thread_run, NULL))
        mexErrMsgIdAndTxt("YMA:MexIO:threadFailed", "Thread creation failed");
    return;
}
