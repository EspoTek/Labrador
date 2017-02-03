#include "winusbdriver.h"

#define SLEEP_DIVIDER 16

winUsbDriver::winUsbDriver(QWidget *parent) : genericUsbDriver(parent)
{
    //This opens the USB connection.  Nothing can continue until the board is up and running.
    bool connected = false;
    while(!connected){
        for (int n=0;n<SLEEP_DIVIDER;n++){
            QThread::msleep(USB_RECONNECT_PERIOD/SLEEP_DIVIDER);
            QCoreApplication::processEvents();
        }
        connected = usbInit(0x03eb, 0xa000);
    }

    //Below is platform-independent constructor code.
    //I can't stick it in usbDriverGeneric since this needs to be run _after_ USB has initialised and calling virtuals from the superclass constructor is a bad idea!
    //You don't need to understand it, but it needs to go in the constructor of all platform-specific drivers!
    //(Actually, I think you could get away with omitting the first two lines but they don't hurt!)
    setDeviceMode(deviceMode);
    newDig(digitalPinState);
    usbIsoInit();

    psuTimer = new QTimer();
    psuTimer->setTimerType(Qt::PreciseTimer);
    psuTimer->start(PSU_PERIOD);
    connect(psuTimer, SIGNAL(timeout()), this, SLOT(psuTick()));
}

winUsbDriver::~winUsbDriver(void){    

    //Like any decent destructor, this just frees resources

    qDebug() << "\n\nwinUsbDriver destructor ran!";
    for (unsigned char k=0; k<NUM_ISO_ENDPOINTS; k++){
        for(int n=0;n<NUM_FUTURE_CTX;n++){
            IsoK_Free(isoCtx[k][n]);
        }
        for(int i=0;i<MAX_OVERLAP;i++){
            OvlK_Release(ovlkHandle[k][i]);
        }
        UsbK_FlushPipe(handle, pipeID[k]);
        UsbK_AbortPipe(handle, pipeID[k]);
    }
    OvlK_Free(ovlPool);
    free(outBuffers[0]);
    free(outBuffers[1]);
    UsbK_Free(handle);
}

unsigned char winUsbDriver::usbInit(unsigned long VIDin, unsigned long PIDin){

    //This function gets you a USB handle, as well as any other data needed to send a control transfer over USB.
    //You should be able to call usbSendControl() immediately after this function has returned success!!

    unsigned char success;
    KLST_DEVINFO_HANDLE deviceInfo = NULL;
    UINT deviceCount = 0;
    DWORD ec = ERROR_SUCCESS;
    KLST_HANDLE deviceList = NULL;

    //List libusbk devices connected
    if (!LstK_Init(&deviceList, (KLST_FLAG) 0))	{
        qDebug("Error initializing device list");
        return 0;
    } //else qDebug() << "Device List initialised!";

    /*
    LstK_Count(deviceList, &deviceCount);
    if (!deviceCount) {
        qDebug("Device list empty");
        LstK_Free(deviceList);	// If LstK_Init returns TRUE, the list must be freed.
        return 0;
    } //else qDebug() << "Device Count initialised!";
*/

    //Look for Labrador!
    LstK_FindByVidPid(deviceList, VIDin, PIDin, &deviceInfo);
    LstK_Free(deviceList);
    if (deviceInfo == NULL){
        qDebug("Could not find device VID = %04X, PID = %04X", VIDin, PIDin);
        return 0;
    }

    //Open Labrador!!
    success = UsbK_Init(&handle, deviceInfo);
    if (!success){
        ec = GetLastError();
        qDebug("UsbK_Init failed. ErrorCode: %08Xh", ec);
    } else qDebug("Device opened successfully!");

    return success;
}

void winUsbDriver::usbSendControl(uint8_t RequestType, uint8_t Request, uint16_t Value, uint16_t Index, uint16_t Length, unsigned char *LDATA){

    //This function sends a control transfer over USB.  It only needs to send data; not receive.
    //LDATA is a pointer to the buffer that is going to be sent to the device.  If no buffer is to be sent, LDATA should be NULL (and any implementation should be able to handle this case!!).
    //The Linux implementation of this is trivially simple.  Have a look!

    //////////////////////////////////////////////////////////////////////////////////////////
    //IF YOU'RE SEEING AN ERROR, CHECK THAT REQUESTTYPE AND REQUEST ARE FORMATTED AS HEX
    //////////////////////////////////////////////////////////////////////////////////////////    

    WINUSB_SETUP_PACKET setupPacket;
    unsigned char controlSuccess;
    UINT bytesTransferred = 0;
    unsigned char *controlBuffer;

    //Error checking
    if (handle==NULL){
        qDebug("Null handle error in usbSendControl");
        return;
    }

    //Fill the setup packet
    setupPacket.RequestType = RequestType;
    setupPacket.Request = Request;
    setupPacket.Value = Value;
    setupPacket.Index = Index;
    setupPacket.Length = Length;

    //Check for case of null LDATA
    if (LDATA==NULL){
        controlBuffer = inBuffer;
    }
    else controlBuffer = LDATA;

    //Send the packet
    controlSuccess = UsbK_ControlTransfer(handle, setupPacket, controlBuffer, setupPacket.Length, &bytesTransferred, NULL);
    if (controlSuccess) {
        qDebug("%d BYTES TRANSFERRED", bytesTransferred);
    }
    else qDebug("usbSendControl failed");
}

unsigned char winUsbDriver::usbIsoInit(void){
    //Iso is slightly less easy than plain old USB.
    //You must set up NUM_FUTURE_CTX iso transfers, with each transfer containing ISO_PACKETS_PER_CTX isochronous packets.
    //These transactions are numbered by n = 0,1,2,3...NUM_FUTURE_CTX-1.  Transfer n should read data into dataBuffer[n].

    //Do note that current implementations don't support changing FPS at runtime.  Some changes will need to be made to enable this (perhaps taking NUM_FUTURE_CTX and ISO_PACKETS_PER_CTX as inputs that the user can change??)


    int n;
    bool success;
    DWORD errorCode = ERROR_SUCCESS;

    //Setting up overlapped I/O.  It's easier than threading on Windows.
    success = OvlK_Init(&ovlPool, handle, MAX_OVERLAP, (KOVL_POOL_FLAG) 0);
    if(!success){
        errorCode = GetLastError();
        qDebug() << "OvlK_Init failed with error code" << errorCode;
        return 0;
    }
    for (unsigned char k=0;k<NUM_ISO_ENDPOINTS;k++){
        success = UsbK_ResetPipe(handle, pipeID[k]);
        if(!success){
            errorCode = GetLastError();
            qDebug() << "UsbK_ResetPipe failed with error code" << errorCode;
            return 0;
        }
    }

    //Filling the transfer contexts
    for(n=0;n<NUM_FUTURE_CTX;n++){
        for (unsigned char k=0;k<NUM_ISO_ENDPOINTS;k++){
            success = IsoK_Init(&isoCtx[k][n], ISO_PACKETS_PER_CTX, n*ISO_PACKETS_PER_CTX);
            if(!success){
                errorCode = GetLastError();
                qDebug() << "IsoK_Init failed with error code" << errorCode;
                qDebug() << "n =" << n;
                return 0;
            }

            success = IsoK_SetPackets(isoCtx[k][n], ISO_PACKET_SIZE);
            if(!success){
                errorCode = GetLastError();
                qDebug() << "IsoK_SetPackets failed with error code" << errorCode;
                qDebug() << "n =" << n;
                return 0;
            }

            success = OvlK_Acquire(&ovlkHandle[k][n], ovlPool);
            if(!success){
                errorCode = GetLastError();
                qDebug() << "OvlK_Acquire failed with error code" << errorCode;
                qDebug() << "n =" << n;
                return 0;
            }

            //Sending the transfer requests
            success = UsbK_IsoReadPipe(handle, pipeID[k], dataBuffer[k][n], sizeof(dataBuffer[k][n]), (LPOVERLAPPED) ovlkHandle[k][n], isoCtx[k][n]);
            //qDebug() << "sizeof(dataBuffer[k][n]) = " << sizeof(dataBuffer[k][n]);
        }
    }

    //Setting up isoTimer.  This will call isoTimerTick every ISO_TIMER_PERIOD milliseconds.
    isoTimer = new QTimer();
    isoTimer->setTimerType(Qt::PreciseTimer);
    isoTimer->start(ISO_TIMER_PERIOD);
    connect(isoTimer, SIGNAL(timeout()), this, SLOT(isoTimerTick()));

    qDebug() << "Setup successful!";
    return 1;
}

void winUsbDriver::isoTimerTick(void){
    //This function is called every ISO_TIMER_PERIOD milliseconds, after usbIsoInit() has run.
    //It should check if a transfer is complete, then copy the ___earliest___ transfer into the appropriate outBuffer, as well as set appropriate bufferLengths.
    //Once this is complete, it should resubmit the transfer that it read the data from.
    //Finally, it should signal upTick() so that isoDriver knows it can draw a new frame.

    timerCount++;
    char subString[3] = "th";
    if(timerCount%10 == 1) strcpy(subString, "st");
    if(timerCount%10 == 2) strcpy(subString, "nd");
    if(timerCount%10 == 3) strcpy(subString, "rd");
    if((timerCount<20) && (timerCount > 10)) strcpy(subString, "th");

    //qDebug("\n\nThis is the %d%s Tick!", timerCount, subString);

    bool success;
    DWORD errorCode = ERROR_SUCCESS;
    int n, earliest = MAX_OVERLAP;
    unsigned int minFrame = 4294967295;
    unsigned int dataBufferOffset;
    unsigned int packetLength = 0;

    //Getting earliest transfer number.
    for (n=0; n<NUM_FUTURE_CTX; n++){
        if(OvlK_IsComplete(ovlkHandle[0][n]) && OvlK_IsComplete(ovlkHandle[1][n]) && OvlK_IsComplete(ovlkHandle[2][n])){
            if(isoCtx[0][n]->StartFrame < minFrame){
                minFrame = isoCtx[0][n]->StartFrame;
                earliest = n;
            }
        }
    }

    //qDebug() << n << "is the earliest!";

    if (earliest == MAX_OVERLAP){
        return;
    }

    //Copy the tranfer data into buffer
    for(int i=0;i<isoCtx[0][earliest]->NumberOfPackets;i++){
        for(unsigned char k=0; k<NUM_ISO_ENDPOINTS;k++){
            dataBufferOffset = isoCtx[k][earliest]->IsoPackets[i].Offset;
            memcpy(&(outBuffers[currentWriteBuffer][packetLength]), &dataBuffer[k][earliest][dataBufferOffset], isoCtx[k][earliest]->IsoPackets[i].Length);
            packetLength += isoCtx[k][earliest]->IsoPackets[i].Length;
        }
    }

    //Get the data for isoRead() ready and swap buffers
    bufferLengths[currentWriteBuffer] = packetLength;
    currentWriteBuffer = !currentWriteBuffer;

    //Zero length packet means something's gone wrong.  Probably a disconnect.
    //In the Linux version, this check is implemented as a timer that attempts a control packet every 250ms.
    //It doesn't matter how you do it, but it's important that there's some code that checks for device disconnects periodically and, if detected, emits the killMe() signal.
    if(packetLength == 0){
        qDebug() << "Zero length iso packet.  An hero!";
        killMe();
    }

    UINT oldStart;
    //Setup transfer for resubmission
    for(unsigned char k=0; k<NUM_ISO_ENDPOINTS; k++){
        oldStart = isoCtx[k][earliest]->StartFrame;
        success = IsoK_ReUse(isoCtx[k][earliest]);
        if(!success){
            errorCode = GetLastError();
            qDebug() << "IsoK_Init failed with error code" << errorCode;
            qDebug() << "n =" << n;
            return;
        }
        isoCtx[k][earliest]->StartFrame = oldStart + ISO_PACKETS_PER_CTX*NUM_FUTURE_CTX;

        success = OvlK_ReUse(ovlkHandle[k][earliest]);
        if(!success){
            errorCode = GetLastError();
            qDebug() << "OvlK_ReUse failed with error code" << errorCode;
            qDebug() << "n =" << n;
            return;
        }
        //Resubmit the transfer
        success = UsbK_IsoReadPipe(handle, pipeID[k], dataBuffer[k][earliest], sizeof(dataBuffer[k][earliest]), (LPOVERLAPPED) ovlkHandle[k][earliest], isoCtx[k][earliest]);
    }

    //Signal to isoDriver that it can draw a new frame.
    upTick();
    return;
}

char *winUsbDriver::isoRead(unsigned int *newLength){
    //This will be called almost immediately after the upTick() signal is sent.  Make sure bufferLengths[] abd outBuffers[] are ready!
    *(newLength) = bufferLengths[!currentWriteBuffer];
    return (char*) outBuffers[(unsigned char) !currentWriteBuffer];
}
