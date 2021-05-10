// Copyright (C) 2018 Christopher Paul Esposito
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

//LIBRADOR INCLUDES
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "libusb.h"
#include "librador.h"

//MISC INCLUDES
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    //I/O
    double *ptr_channel_in;
    double *ptr_sampleRate_hz_in;
    double *ptr_delay_seconds_in;
    double *ptr_timeWindow_seconds_in;
    //double *ptr_length_out;
    uint8_t *ptr_data_out;
    mwSize dims[2] = {0,0};
    int ndims = 2;

    //Internals
    int channel;
    double sampleRate_hz;
    double delay_seconds;
    double timeWindow_seconds;
    int* length_int;
    std::vector<uint8_t>* dll_return;

    //Fetch inputs.
    ptr_channel_in = mxGetPr(prhs[0]); //Mex get pointer to real (double);
    ptr_timeWindow_seconds_in = mxGetPr(prhs[1]);
    ptr_sampleRate_hz_in = mxGetPr(prhs[2]);
    ptr_delay_seconds_in = mxGetPr(prhs[3]);

    //Copy to internals
    channel = (int)(*ptr_channel_in);
    sampleRate_hz = (*ptr_sampleRate_hz_in);
    delay_seconds = (*ptr_delay_seconds_in);
    timeWindow_seconds = (*ptr_timeWindow_seconds_in);
    length_int = (int*)mxCalloc(1, sizeof(int));

    //Actually get the data.
    dll_return = librador_get_digital_data(channel, timeWindow_seconds, sampleRate_hz, delay_seconds);
    length_int[0] = dll_return->size();

    //Abort now if there's no data!!!
    if(dll_return == NULL){
        dims[0] = 1;
        dims[1] = 1;
        plhs[0] = mxCreateNumericArray(ndims, dims, mxDOUBLE_CLASS, mxREAL);
        double *ptr_zero = (double *) mxCalloc(1, sizeof(double));
        ptr_zero[0] = 0;
        mxSetData(plhs[0], ptr_zero);
        return;
    }

    //Malloc all the outputs!
    //We need to copy from the DLL to MATLAB so that it can work with the data without cracking the sads.
    ptr_data_out = (uint8_t*)mxCalloc(length_int[0], sizeof(uint8_t));
    memcpy(ptr_data_out, dll_return->data(), length_int[0] * sizeof(uint8_t));
    dims[0] = 1;
    dims[1] = length_int[0];

    //plhs[0] = mxCreateDoubleScalar((double)ptr_length_out[0]);
    plhs[0] = mxCreateNumericArray(ndims, dims, mxUINT8_CLASS, mxREAL);
    mxSetData(plhs[0], ptr_data_out);
}
