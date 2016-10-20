#include "winusbdriver.h"

winUsbDriver::winUsbDriver(QWidget *parent) : genericUsbDriver(parent)
{
    qDebug() << "Making USB Driver invisible!!";
    this->hide();
    //Load stack so that reset signal can be sent

    outBuffers[0] = (unsigned char *) calloc(ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX + 8, 1);
    outBuffers[1] = (unsigned char *) calloc(ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX + 8, 1);

    bufferLengths[0] = 0;
    bufferLengths[1] = 0;

    bool connected = false;
    while(!connected){
        QThread::msleep(32);
        connected = usbInit(0x03eb, 0xa000);
    }
    setDeviceMode(deviceMode);
    newDig(digitalPinState);
    usbIsoInit();


    psuTimer = new QTimer();
    psuTimer->setTimerType(Qt::PreciseTimer);
    psuTimer->start(PSU_PERIOD);
    connect(psuTimer, SIGNAL(timeout()), this, SLOT(psuTick()));
}

winUsbDriver::~winUsbDriver(void){
    qDebug() << "\n\nwinUsbDriver destructor ran!";
    for(int n=0;n<NUM_FUTURE_CTX;n++){
        IsoK_Free(isoCtx[n]);
    }
    for(int i=0;i<MAX_OVERLAP;i++){
        OvlK_Release(ovlkHandle[i]);
    }
    UsbK_FlushPipe(handle, pipeID);
    UsbK_AbortPipe(handle, pipeID);
    OvlK_Free(ovlPool);
    free(outBuffers[0]);
    free(outBuffers[1]);
    UsbK_Free(handle);
}

unsigned char winUsbDriver::usbInit(unsigned long VIDin, unsigned long PIDin){
    unsigned char success;
    KLST_DEVINFO_HANDLE deviceInfo = NULL;
    UINT deviceCount = 0;
    DWORD ec = ERROR_SUCCESS;
    KLST_HANDLE deviceList = NULL;


    //qDebug() << "usbInit() entered";
    if (!LstK_Init(&deviceList, (KLST_FLAG) 0))	{
        qDebug("Error initializing device list");
        return 0;
    } //else qDebug() << "Device List initialised!";

    LstK_Count(deviceList, &deviceCount);
    if (!deviceCount) {
        qDebug("Device list empty");
        LstK_Free(deviceList);	// If LstK_Init returns TRUE, the list must be freed.
        return 0;
    } //else qDebug() << "Device Count initialised!";

    //qDebug("Looking for device VID = %04X, PID = %04X\n", VIDin, PIDin);

    LstK_FindByVidPid(deviceList, VIDin, PIDin, &deviceInfo);
    LstK_Free(deviceList);
    if (deviceInfo){
        /*qDebug("Using %04X:%04X (%s): %s - %s\n",
            deviceInfo->Common.Vid,
            deviceInfo->Common.Pid,
            deviceInfo->Common.InstanceID,
            deviceInfo->DeviceDesc,
            deviceInfo->Mfg);
            Causes exceptions in debug mode!!!!*/
    }
    else {
        qDebug("Could not find device VID = %04X, PID = %04X", VIDin, PIDin);
        return 0;
    }

    success = UsbK_Init(&handle, deviceInfo);
    if (!success){
        ec = GetLastError();
        qDebug("UsbK_Init failed. ErrorCode: %08Xh", ec);
    } else qDebug("Device opened successfully!");

    return success;
}

void winUsbDriver::usbSendControl(uint8_t RequestType, uint8_t Request, uint16_t Value, uint16_t Index, uint16_t Length, unsigned char *LDATA){

    //////////////////////////////////////////////////////////////////////////////////////////
    //IF YOU'RE SEEING AN ERROR, CHECK THAT REQUESTTYPE AND REQUEST ARE FORMATTED AS HEX
    //////////////////////////////////////////////////////////////////////////////////////////

    WINUSB_SETUP_PACKET setupPacket;
    unsigned char controlSuccess;
    UINT bytesTransferred = 0;
    unsigned char *controlBuffer;

    if (handle==NULL){
        qDebug("Null handle error in usbSendControl");
        return;
    }
    setupPacket.RequestType = (UCHAR) RequestType;
    setupPacket.Request = (UCHAR) Request;
    setupPacket.Value = (USHORT) Value;
    setupPacket.Index = (USHORT) Index;
    setupPacket.Length = (USHORT) Length;

    //qDebug("RequestType = %x, Request = %x, Value = %u, Index = %u, Length = %u", setupPacket.RequestType, setupPacket.Request, setupPacket.Value, setupPacket.Index, setupPacket.Length);

    if (LDATA==NULL){
        controlBuffer = (unsigned char *) malloc(256);
    }
    else controlBuffer = LDATA;

    //qDebug() << controlBuffer;
    //qDebug() << handle;

    //qDebug("SENDING CONTROL PACKET\n");
    controlSuccess = UsbK_ControlTransfer(handle, setupPacket, controlBuffer, setupPacket.Length, &bytesTransferred, NULL);
    if (controlSuccess) {
        qDebug("%d BYTES TRANSFERRED", bytesTransferred);
    }
    else qDebug("usbSendControl failed");

    if(LDATA == NULL){
        free(controlBuffer);
    }
}

unsigned char winUsbDriver::usbIsoInit(void){
    //Setup the iso stack
    int n;
    bool success;
    DWORD errorCode = ERROR_SUCCESS;

    success = OvlK_Init(&ovlPool, handle, MAX_OVERLAP, (KOVL_POOL_FLAG) 0);
    if(!success){
        errorCode = GetLastError();
        qDebug() << "OvlK_Init failed with error code" << errorCode;
        return 0;
    }
    success = UsbK_ResetPipe(handle, pipeID);
    if(!success){
        errorCode = GetLastError();
        qDebug() << "UsbK_ResetPipe failed with error code" << errorCode;
        return 0;
    }

    for(n=0;n<NUM_FUTURE_CTX;n++){
        success = IsoK_Init(&isoCtx[n], ISO_PACKETS_PER_CTX, n*ISO_PACKETS_PER_CTX);
        if(!success){
            errorCode = GetLastError();
            qDebug() << "IsoK_Init failed with error code" << errorCode;
            qDebug() << "n =" << n;
            return 0;
        }

        success = IsoK_SetPackets(isoCtx[n], ISO_PACKET_SIZE);
        if(!success){
            errorCode = GetLastError();
            qDebug() << "IsoK_SetPackets failed with error code" << errorCode;
            qDebug() << "n =" << n;
            return 0;
        }

        success = OvlK_Acquire(&ovlkHandle[n], ovlPool);
        if(!success){
            errorCode = GetLastError();
            qDebug() << "OvlK_Acquire failed with error code" << errorCode;
            qDebug() << "n =" << n;
            return 0;
        }

        success = UsbK_IsoReadPipe(handle, pipeID, dataBuffer[n], sizeof(dataBuffer[n]), (LPOVERLAPPED) ovlkHandle[n], isoCtx[n]);
    }

    isoTimer = new QTimer();
    isoTimer->setTimerType(Qt::PreciseTimer);
    isoTimer->start(ISO_TIMER_PERIOD);
    connect(isoTimer, SIGNAL(timeout()), this, SLOT(isoTimerTick()));

    qDebug() << "Setup successful!";
    return 1;
}

void winUsbDriver::isoTimerTick(void){
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

    for (n=0; n<NUM_FUTURE_CTX; n++){
        if(OvlK_IsComplete(ovlkHandle[n])){
            //qDebug("Transfer %d is complete!!", n);
            if(isoCtx[n]->StartFrame < minFrame){
                minFrame = isoCtx[n]->StartFrame;
                earliest = n;
            }
        }
    }

    if (earliest == MAX_OVERLAP){
        return;
    }

    //qDebug() << "Max =" << ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX + 8;
    //Copy iso data into buffer
    for(int i=0;i<isoCtx[earliest]->NumberOfPackets;i++){
        dataBufferOffset = isoCtx[earliest]->IsoPackets[i].Offset;
        //qDebug() << packetLength;
        memcpy(&(outBuffers[currentWriteBuffer][packetLength]), &dataBuffer[earliest][dataBufferOffset], isoCtx[earliest]->IsoPackets[i].Length);
        packetLength += isoCtx[earliest]->IsoPackets[i].Length;
    }
    //Control data for isoDriver
    bufferLengths[currentWriteBuffer] = packetLength;
    currentWriteBuffer = !currentWriteBuffer;

    //Zero length packet means something's gone wrong.  Probably a disconnect.
    if(packetLength == 0){
        qDebug() << "Zero length iso packet.  An hero!";
        killMe();
    }

    //Setup next transfer
    UINT oldStart = isoCtx[earliest]->StartFrame;
    success = IsoK_ReUse(isoCtx[earliest]);
    if(!success){
        errorCode = GetLastError();
        qDebug() << "IsoK_Init failed with error code" << errorCode;
        qDebug() << "n =" << n;
        return;
    }
    isoCtx[earliest]->StartFrame = oldStart + ISO_PACKETS_PER_CTX*NUM_FUTURE_CTX;
    //qDebug() << oldStart;
    //qDebug() << isoCtx[n]->StartFrame;

    success = OvlK_ReUse(ovlkHandle[earliest]);
    if(!success){
        errorCode = GetLastError();
        qDebug() << "OvlK_ReUse failed with error code" << errorCode;
        qDebug() << "n =" << n;
        return;
    }
    success = UsbK_IsoReadPipe(handle, pipeID, dataBuffer[earliest], sizeof(dataBuffer[earliest]), (LPOVERLAPPED) ovlkHandle[earliest], isoCtx[earliest]);
    //qDebug("%d bytes will go to isoDriver", packetLength);
    upTick();
    return;
}

char *winUsbDriver::isoRead(unsigned int *newLength){
    //unsigned char *returnBuffer;
    //returnBuffer = (unsigned char *) malloc(numSamples + 8); //8-byte header contains (unsigned long) length
    //((unsigned int *)returnBuffer)[0] = 0;
    //return (char*) returnBuffer;
    //qDebug() << (unsigned char) !currentWriteBuffer;
    *(newLength) = bufferLengths[!currentWriteBuffer];
    return (char*) outBuffers[(unsigned char) !currentWriteBuffer];
}
