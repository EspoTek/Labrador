#define COMPILING_WITH_OCTAVE

//MATLAB INCLUDES
#ifndef COMPILING_WITH_OCTAVE
  #include <matrix.h>
#endif
#include <mex.h>

//LIBUSB INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include "libusb.h"

//MISC INCLUDES
#include <math.h>
#include <string.h>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    //Raw Inputs
    char *HANDLE_CHAR_RAW_IN, *CTX_CHAR_RAW_IN;
  
    //Processed inputs
    libusb_context *ctx;
    libusb_device_handle *handle;
  
    //Interals
  
    //To export:
    
    //Parse Inputs    
    HANDLE_CHAR_RAW_IN = mxArrayToString(prhs[0]);
    CTX_CHAR_RAW_IN = mxArrayToString(prhs[1]);
        
    sscanf(HANDLE_CHAR_RAW_IN, "%016x", &ctx);
	  sscanf(CTX_CHAR_RAW_IN, "%016x", &handle);
    
    //Delete the handle and the CTX
    mexPrintf("\nFreeing the following Libusb structures:\n");
    mexPrintf("Interface: Handle 0x%016x, Interface 0\n", handle);
    mexPrintf("Handle: 0x%016x\n", handle);
    mexPrintf("Context: 0x%016x\n", ctx);
    
    libusb_release_interface(handle, 0);
    mexPrintf("Interface released\n");
    libusb_close(handle);
    mexPrintf("Device Closed\n");
    //Early return here, seems to prevent Octave from crashing (or normal exit, Ubuntu isn't complaining???)
    mexPrintf("To prevent a crash in Octave, the Libusb Context was not exited completely.\nThe device handles should all be free, however.\n");
    return;
    
    libusb_exit(ctx);
    mexPrintf("Libusb exited\n");
    return;    
}
