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
    bool state_on;
        
    //Map the inputs
    double * ptr_channel = mxGetPr(prhs[0]);
    channel = (int)(*ptr_channel);
    
    double * ptr_state_on = mxGetPr(prhs[0]);
    state_on = (bool)(*ptr_state_on);

    //I/O
    int *ptr_return_value;
  
    //Malloc all the vars!
    ptr_return_value = (int *) calloc(1, sizeof(int));
    
    //Send the command
    ptr_return_value[0] = librador_set_digital_out(channel, state_on);

    plhs[0] = mxCreateDoubleScalar(ptr_return_value[0]);   
}