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
    char *VID_CHAR_RAW_IN, *PID_CHAR_RAW_IN;
  
    //Processed inputs
    unsigned int VID, PID;
    libusb_context *old_ctx;
  
    //Interals
    libusb_context *ctx;
    libusb_device_handle *handle;
  
    //To export:
    char handle_string[17];  //128 bits allocated, including char.
    char ctx_string[17];
    
    //Parse Inputs    
    VID_CHAR_RAW_IN = mxArrayToString(prhs[0]);
    PID_CHAR_RAW_IN = mxArrayToString(prhs[1]);
    
    printf("VID=%s\n", VID_CHAR_RAW_IN);
    printf("PID=%s\n", PID_CHAR_RAW_IN);
    
    sscanf(VID_CHAR_RAW_IN, "%4x", &VID);
	  sscanf(PID_CHAR_RAW_IN, "%04x", &PID);    
    
    //Initialise the Library
    int error;
    error = libusb_init(&ctx);
    if(error){
        mexPrintf("libusb_init FAILED\n");
        goto return_zeros;
    } else mexPrintf("Libusb context initialised\n");
    libusb_set_debug(ctx, 3);
    
    //Get a handle on the Labrador device
    handle = libusb_open_device_with_vid_pid(ctx, VID, PID);
    if(handle==NULL){
        mexPrintf("DEVICE NOT FOUND\n");
        goto abort_libusb_open;
    }
    mexPrintf("Device found!!\n");

    //Claim the interface
    error = libusb_claim_interface(handle, 0);
    if(error){
        mexPrintf("libusb_claim_interface FAILED\n");
        goto abort_libusb_claim_interface;
    } else mexPrintf("Interface claimed!\n");

    mexPrintf("Handle is %d bytes long\n", sizeof(handle));
    mexPrintf("Handle data is 0x%016x\n", handle);
    mexPrintf("Context is %d bytes long\n", sizeof(ctx));
    mexPrintf("Context data is 0x%016x\n", ctx);

    sprintf(handle_string, "%016x", handle);
    sprintf(ctx_string, "%016x", ctx);
    
    mexPrintf("\nConverting values...  Ensure they're unchanged!\n");
    mexPrintf("Handle: %s\n",handle_string);
    mexPrintf("Context: %s\n", ctx_string);

    
    plhs[0] = mxCreateString(handle_string);   
    plhs[1] = mxCreateString(ctx_string);   
        
    return; 
    
    abort_libusb_claim_interface:
    libusb_close(handle);
    mexPrintf("Device Closed\n");

    abort_libusb_open:
    libusb_exit(ctx);
    mexPrintf("Libusb exited\n");
    
    return_zeros:
    sprintf(handle_string, "%016x", 0);
    sprintf(ctx_string, "%016x", 0);

    plhs[0] = mxCreateString(handle_string);   
    plhs[1] = mxCreateString(ctx_string);   
    return;
}
