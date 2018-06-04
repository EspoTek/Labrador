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
#include <sys/time.h>
#include <sys/resource.h>

//Defines
#define ISO_PACKET_SIZE (750)
#define NUM_ISO_ENDPOINTS (1)
#define ISO_PACKETS_PER_CTX (33)
#define NUM_FUTURE_CTX (1)

//Typedef
typedef struct libusb_transfer libusb_transfer;
typedef struct timeval timeval;
typedef struct thread_data {
  libusb_context *ctx;
} thread_data;  

  
//Second thread to check for libusb complete
void *thread_run(thread_data *thread_init)
{
    //Copied inputs
    libusb_context *ctx;
    timeval tv;
  
    //Setup
    tv.tv_sec = 1;
    tv.tv_usec = 100000;
    mexPrintf("Libusb thread created\n");
    //Copy the thread data
    ctx = thread_init->ctx;
    mexPrintf("Context: %016x\n", ctx);

    //Main loop
    while(1){
      if(libusb_event_handling_ok(ctx)){
        libusb_handle_events_timeout(ctx, &tv);
        mexPrintf("libusb_handle_events_timeout completed!\n");
        } else {
          mexPrintf("Cannot handle libusb events.  Backing off...");
          usleep(100000);
        }
    }
}  

//Callback on iso transfer complete.
static void LIBUSB_CALL isoCallback(struct libusb_transfer * transfer){

    int ctx_number;
      
    if(transfer->status!=LIBUSB_TRANSFER_CANCELLED){
        ctx_number = ((int *)transfer->user_data);
    }
    return;
    
    mexPrintf('Transfer %d done!\n', ctx_number);
}

//Main mex function
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
  
    //Code to set stack size after compilation
    //https://stackoverflow.com/questions/2275550/change-stack-size-for-a-c-application-in-linux-during-compilation-with-gnu-com
    const rlim_t kStackSize = 128 * 1024 * 1024;   // min stack size = 128 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                mexPrintf("setrlimit returned result = %d\n", result);
            }
        }
    } else mexPrintf("Result was not zero!\n");


  /*
    char test1_string[9] = "12345678";
    char test2_string[9] = "abcdabcd";
  
    int test1_int;
    int test2_int;
    sscanf(test1_string, "%x", &test1_int);
    sscanf(test2_string, "%x", &test2_int);
    
    mexPrintf("test1_int = %x\n", test1_int);
    mexPrintf("test1_string = %s\n", test1_string);
    mexPrintf("test2_int = %x\n", test2_int);
    mexPrintf("test2_string = %s\n", test2_string);
*/
    //Raw Inputs
    char *HANDLE_CHAR_RAW_IN;
    char *CTX_CHAR_RAW_IN;
    char *PIPE_ID_CHAR_RAW_IN;
  
    //char HANDLE_STRING_ON_STACK[17];
    //char CTX_STRING_ON_STACK[17];

    //Processed inputs
    libusb_context *ctx;
    libusb_device_handle *handle;
    uint8_t pipeID;
  
    //Internals
    libusb_transfer *isoCtx[NUM_ISO_ENDPOINTS][NUM_FUTURE_CTX];
    uint8_t *dataBuffer[NUM_ISO_ENDPOINTS][NUM_FUTURE_CTX];
    int *pointer_to_constant[NUM_FUTURE_CTX];

    //To export:
  
    //Parse Inputs    
    HANDLE_CHAR_RAW_IN = mxArrayToString(prhs[0]);     
    //strcpy(HANDLE_STRING_ON_STACK, HANDLE_CHAR_RAW_IN);
    sscanf(HANDLE_CHAR_RAW_IN, "%x", &handle);
    
    CTX_CHAR_RAW_IN = mxArrayToString(prhs[1]);
    //strcpy(CTX_STRING_ON_STACK, CTX_CHAR_RAW_IN);
	  sscanf(CTX_CHAR_RAW_IN, "%x", &ctx);

    PIPE_ID_CHAR_RAW_IN = mxArrayToString(prhs[2]);
	  sscanf(PIPE_ID_CHAR_RAW_IN, "%2x", &pipeID);
    
    mexPrintf("\npipeID = %d\n", pipeID);
    mexPrintf("Handle String : %s\n", HANDLE_CHAR_RAW_IN);
    mexPrintf("Handle = %016x\n", (unsigned long)handle);
    mexPrintf("Context String : %s\n", CTX_CHAR_RAW_IN);
    mexPrintf("Context = %016x\n\n", (unsigned long)ctx);
    
    //Allocate the constant numbers;
    int error, n;
    unsigned char k;
    
    for(n=0; n<NUM_FUTURE_CTX; n++){
      pointer_to_constant[n] = malloc(sizeof(int));
      *(pointer_to_constant[n]) = n;
    }
    
    //Set up the transfers
    for(n=0;n<NUM_FUTURE_CTX;n++){
        for (k=0;k<NUM_ISO_ENDPOINTS;k++){
            isoCtx[k][n] = libusb_alloc_transfer(ISO_PACKETS_PER_CTX);
            if(isoCtx[k][n] == NULL){
              mexPrintf("libusb_alloc_transfer FAILED\n");
            } else {
              mexPrintf("libusb_alloc_transfer success: isoCtx[%d][%d] = %lx\n", k,n, isoCtx[k][n]);
            }
            dataBuffer[k][n] = malloc(ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX+8);
            libusb_fill_iso_transfer(isoCtx[k][n], handle, pipeID, dataBuffer[k][n], ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX, ISO_PACKETS_PER_CTX, isoCallback, (void*)pointer_to_constant[n], 4000);
            libusb_set_iso_packet_lengths(isoCtx[k][n], ISO_PACKET_SIZE);
        }
    }
    
    //Submit the transfers
    for(n=0;n<NUM_FUTURE_CTX;n++){
        for (k=0;k<NUM_ISO_ENDPOINTS;k++){
            error = libusb_submit_transfer(isoCtx[k][n]);
            if(error){
                mexPrintf("libusb_submit_transfer FAILED\n");
                mexPrintf("ERROR: %s\n",libusb_error_name(error));
            } 
            else {
                mexPrintf("isoCtx submitted successfully!\n");
            }
        }
    }

    //Setup the thread data
    thread_data thread_init;
    thread_init.ctx = ctx;
    
    //Create the libusb thread;
    pthread_t thread;
    error = pthread_create(&thread, NULL, thread_run, &thread_init);
    if(error) mexPrintf("Could not create Libusb thread!");

    //Short sleep to ensure the other thread has enough time to copy everything from memory.  Just in case...
    usleep(100000);

    mexPrintf("Iso Stack initialised!\n");
    return;    
}
