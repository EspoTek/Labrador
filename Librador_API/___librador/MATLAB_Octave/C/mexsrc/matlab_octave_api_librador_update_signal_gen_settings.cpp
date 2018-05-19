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

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    //Define the inputs
    int channel;
    unsigned char* sampleBuffer;
    int numSamples;
    double usecs_between_samples;
    double amplitude_v;
    double offset_v;
         
    //Map the inputs
    double * ptr_channel_double = mxGetPr(prhs[0]);
    channel = (int)(*ptr_channel_double);
    
    double * ptr_numSamples_double = mxGetPr(prhs[2]);
    numSamples = (int)(*ptr_numSamples_double);
    
    double * sampleBuffer_double = mxGetPr(prhs[1]);
    sampleBuffer = (unsigned char*)calloc(numSamples, sizeof(unsigned char));
    for(int i=0; i<numSamples; i++){
      sampleBuffer[i] = sampleBuffer_double[i];
    }
   
    double *ptr_usecs_between_samples = mxGetPr(prhs[3]);
    usecs_between_samples = (*ptr_usecs_between_samples);
    double *ptr_amplitude_v = mxGetPr(prhs[4]);
    amplitude_v = (*ptr_amplitude_v);
    double *ptr_offset_v = mxGetPr(prhs[5]);
    offset_v = (*ptr_offset_v);

    //I/O
    int *ptr_return_value;
  
    //Malloc all the vars!
    ptr_return_value = (int *) calloc(1, sizeof(int));
    
    //Send the command
    ptr_return_value[0] = librador_update_signal_gen_settings(channel, sampleBuffer, numSamples, usecs_between_samples, amplitude_v, offset_v);

    plhs[0] = mxCreateDoubleScalar(ptr_return_value[0]);   
}