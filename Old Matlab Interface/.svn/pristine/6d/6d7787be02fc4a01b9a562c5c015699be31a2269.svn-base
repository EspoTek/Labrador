//MATLAB INCLUDES
#include <matrix.h>
#include <mex.h>

//LIBUSBK INCLUDES
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "libusbk.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    //Vars:
        //Imports
            char* POOL_CHAR;
            char* icx0, icx1;
            char* HANDLE_CHAR;
            KUSB_HANDLE handle = NULL;
            PKISO_CONTEXT isoCtx_zero;
            PKISO_CONTEXT isoCtx_one;
            KOVL_POOL_HANDLE ovlPool = NULL;


    
        //Initialise Data
            POOL_CHAR = mxArrayToString(prhs[0]);  
            sscanf(POOL_CHAR, "%16x", &ovlPool);
            
            icx0 = mxArrayToString(prhs[1]);  
            sscanf(icx0, "%16x", &isoCtx_zero);

            icx1 = mxArrayToString(prhs[2]);  
            sscanf(icx1, "%16x", &isoCtx_one);

            POOL_CHAR = mxArrayToString(prhs[3]);  
            sscanf(POOL_CHAR, "%16x", &ovlPool);


        //Actual Function
            UsbK_Free(handle);
            IsoK_Free(isoCtx_zero);
            IsoK_Free(isoCtx_one);
            OvlK_Free(ovlPool);           
    return;
}