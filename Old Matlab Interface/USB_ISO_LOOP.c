//MATLAB INCLUDES
#include <matrix.h>
#include <mex.h>

//LIBUSBK INCLUDES
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "libusbk.h"

#define DEBUG_SHOWCTRL 1
#define ISO_PACKETS_TO_READ 30
#define ISO_PACKET_SIZE 750
#define HALFBUFFER_SIZE (ISO_PACKETS_TO_READ*ISO_PACKET_SIZE)

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    
    //Vars:
        //Imports
            char *HANDLE_CHAR;
            KUSB_HANDLE handle = NULL;
            char *stm_handle_string;
            KSTM_HANDLE stm_handle = NULL;
            unsigned char pipeID = 0x83;
        //Internals
            unsigned char *tempBuffer;
            unsigned char success;
            DWORD errorCode = ERROR_SUCCESS;
            ULONG length;
            unsigned int n;
        //Exports
            char *transfer_contents;
            unsigned int *error_export;
    
    //Initialise Data
        HANDLE_CHAR = mxArrayToString(prhs[0]);  
        sscanf(HANDLE_CHAR, "%16x", &handle);

        stm_handle_string = mxArrayToString(prhs[1]);  
        sscanf(stm_handle_string, "%16x", &stm_handle);

        //Actual Function
            tempBuffer = mxMalloc(HALFBUFFER_SIZE);
			success = StmK_Read(stm_handle, tempBuffer, 0, HALFBUFFER_SIZE, &length);
            printf("%d bytes copied, out of a possible %d\n", length, HALFBUFFER_SIZE);
			if (!success)	{
				errorCode = GetLastError();
				printf("StmkK_Read failed. ErrorCode: %08Xh\n", errorCode);
                //printf("No more items = %08Xh\n", ERROR_NO_MORE_ITEMS);
			}
        
    //Export Data
            transfer_contents = mxMalloc(HALFBUFFER_SIZE);
            for (n=0;n<HALFBUFFER_SIZE;n++){
                transfer_contents[n] = tempBuffer[n];
            }
            
            plhs[0] = mxCreateNumericMatrix(1,HALFBUFFER_SIZE, mxINT8_CLASS, 0);
            mxSetData(plhs[0], transfer_contents);
            
            error_export = mxMalloc(4);
            error_export[0] = errorCode;
            plhs[1] = mxCreateNumericMatrix(1,1, mxUINT32_CLASS, 0);
            mxSetData(plhs[1], error_export);
}