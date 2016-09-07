//MATLAB INCLUDES
#include <matrix.h>
#include <mex.h>

//LIBUSBK INCLUDES
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "libusbk.h"

//MISC INCLUDES
#include <math.h>
#include <string.h>

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    //Interals
    KLST_HANDLE deviceList = NULL;
	KLST_DEVINFO_HANDLE deviceInfo = NULL;
	DWORD ec = ERROR_SUCCESS;
	UCHAR pipeIndex = 0;
	WINUSB_PIPE_INFORMATION pipeInfo;
   	ULONG VIDin, PIDin;
	ULONG deviceCount = 0;
    //To export:
    KUSB_HANDLE handle = NULL;
    char handle_string[17];
    
    char *VID_CHAR, *PID_CHAR;
    
    VID_CHAR = mxArrayToString(prhs[0]);
    PID_CHAR = mxArrayToString(prhs[1]);
    
    printf("VID=%s\n", VID_CHAR);
    printf("PID=%s\n", PID_CHAR);
    
    sscanf(VID_CHAR, "%4x", &VIDin);
	sscanf(PID_CHAR, "%04x", &PIDin);
    
    	//Init device list!
	if (!LstK_Init(&deviceList, 0))	{
		mexPrintf("Error initializing device list.\n");
		return;
	}
    
    //Check if device list is empty
	LstK_Count(deviceList, &deviceCount);
	if (!deviceCount) {
		mexPrintf("Device list empty.\n");
		LstK_Free(deviceList);	// If LstK_Init returns TRUE, the list must be freed.
		return;
	}

	mexPrintf("Looking for device vid/pid %04X/%04X..\n", VIDin, PIDin);
    
    	//Set device info to the info specified by the INF that belongs to said VID/PID pair
	LstK_FindByVidPid(deviceList, VIDin, PIDin, &deviceInfo);
	if (deviceInfo){
		mexPrintf("Using %04X:%04X (%s): %s - %s\n",
			deviceInfo->Common.Vid,
			deviceInfo->Common.Pid,
			deviceInfo->Common.InstanceID,
			deviceInfo->DeviceDesc,
			deviceInfo->Mfg);
	}
	else {
		mexPrintf("Yeah nah kent couldn't find the device aye\n");
		return;
	}
    
    	// Initialize the device
	if (!UsbK_Init(&handle, deviceInfo)){
		ec = GetLastError();
		mexPrintf("Usb.Init failed. ErrorCode: %08Xh\n", ec);
	}
	mexPrintf("Device opened successfully!\n");
    
    	mexPrintf("Pipe Information:\n");
        while (UsbK_QueryPipe(handle, 0, pipeIndex++, &pipeInfo)){
		mexPrintf("  PipeId=0x%02X PipeType=0x%02X Interval=%u MaximumPacketSize=%u\n",
			pipeInfo.PipeId, pipeInfo.PipeType, pipeInfo.Interval, pipeInfo.MaximumPacketSize);
	}


    mexPrintf("Handle is %d bytes long\n", sizeof(handle));
    mexPrintf("Handle data is 0x%16x\n\n\n\n\n", handle);
    
    sprintf(handle_string, "%016x", handle);
    
    plhs[0] = mxCreateString(handle_string);   
    
    LstK_Free(deviceList);
    
    return;    
}
