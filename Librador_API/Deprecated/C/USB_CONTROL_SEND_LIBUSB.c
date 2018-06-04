#define COMPILING_WITH_OCTAVE

//MATLAB INCLUDES
#ifndef COMPILING_WITH_OCTAVE
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

#define INPUT_BUFFER_SIZE 256

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  /*
    char test1_string[9] = "12345678";
    char test2_string[9] = "abcdabcd";
  
    int test1_int;
    int test2_int;
    sscanf(test1_string, "%x", &test1_int);
    sscanf(test2_string, "%x", &test2_int);
    
    printf("test1_int = %x\n", test1_int);
    printf("test1_string = %s\n", test1_string);
    printf("test2_int = %x\n", test2_int);
    printf("test2_string = %s\n", test2_string);
*/
    
    //Raw Inputs
    char *HANDLE_CHAR_RAW_IN;
    char *CTX_CHAR_RAW_IN;
    char *REQUEST_TYPE_RAW_IN;
    char *REQUEST_RAW_IN;
    char *VALUE_RAW_IN;
    char *INDEX_RAW_IN;
    char *LENGTH_RAW_IN;
    
    char HANDLE_STRING_ON_STACK[17];
    char CTX_STRING_ON_STACK[17];
  
    //Processed inputs
    libusb_context *ctx;
    libusb_device_handle *handle;
    uint8_t RequestType;
    uint8_t Request;
    uint16_t Value;
    uint16_t Index;
    uint16_t Length;
  
    //Interals
    unsigned char *controlBuffer;
    uint64_t temp_read_handle, temp_read_ctx;
  
    //To export:
    mwSize dims[2] = {1,INPUT_BUFFER_SIZE};
    unsigned char *out_ptr;
  
    //Parse Inputs    
    HANDLE_CHAR_RAW_IN = mxArrayToString(prhs[0]);     
    //strcpy(HANDLE_STRING_ON_STACK, HANDLE_CHAR_RAW_IN);
    sscanf(HANDLE_CHAR_RAW_IN, "%x", &handle);
    
    CTX_CHAR_RAW_IN = mxArrayToString(prhs[1]);
    //strcpy(CTX_STRING_ON_STACK, CTX_CHAR_RAW_IN);
	  sscanf(CTX_CHAR_RAW_IN, "%x", &ctx);
    
    REQUEST_TYPE_RAW_IN = mxArrayToString(prhs[2]);  
    sscanf(REQUEST_TYPE_RAW_IN, "%2x", &RequestType);

    REQUEST_RAW_IN = mxArrayToString(prhs[3]);  
    sscanf(REQUEST_RAW_IN, "%2x", &Request);

    VALUE_RAW_IN = mxArrayToString(prhs[4]);  
    sscanf(VALUE_RAW_IN, "%4x", &Value);
  
    INDEX_RAW_IN = mxArrayToString(prhs[5]);  
    sscanf(INDEX_RAW_IN, "%4x", &Index);
    
    LENGTH_RAW_IN = mxArrayToString(prhs[6]);  
    sscanf(LENGTH_RAW_IN, "%4x", &Length);        
   
    mexPrintf("\nHandle String : %s\n", HANDLE_CHAR_RAW_IN);
    mexPrintf("Handle = %016x\n", (unsigned long)handle);

    mexPrintf("Context String : %s\n", CTX_CHAR_RAW_IN);
    mexPrintf("Context = %016x\n\n", (unsigned long)ctx);
    
    
    //Allocate buffer memory if it's an IN transaction.  Set it to an input pointer if it's an OUT.
    if(Request & 0x80){
      controlBuffer = mxMalloc(INPUT_BUFFER_SIZE);
    } else controlBuffer = mxGetData(prhs[7]);

    
    //Send the packet
    int error;
    mexPrintf("Length = %hu\n", Length);
    error = libusb_control_transfer(handle, RequestType, Request, Value, Index, controlBuffer, Length, 4000);
    if(error<0){
      mexPrintf("Error number: %d\n", error);
      mexPrintf("libusb_control_transfer FAILED with error %s\n", libusb_error_name(error));
    }
    
    plhs[0] = mxCreateNumericArray(2, dims, mxUINT8_CLASS, mxREAL);
    
    //Setup function output.
    int n;
    out_ptr = mxMalloc(INPUT_BUFFER_SIZE);
    
    //Copy data , even if it's not an IN transaction.
    for (n=0;n<INPUT_BUFFER_SIZE;n++){
        out_ptr[n] = controlBuffer[n];
    }
    
    plhs[0] = mxCreateNumericArray(2, dims, mxUINT8_CLASS, mxREAL);
    mxSetData(plhs[0], out_ptr);
    
    return;    
}
