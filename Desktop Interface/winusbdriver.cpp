#include "winusbdriver.h"

winUsbDriver::winUsbDriver(QWidget *parent) : QLabel(parent)
{
    qDebug() << "Making USB Driver invisible!!";
    this->hide();
    //Load stack so that reset signal can be sent
    firstConnect = usbInit(0x03eb, 0xa000);
    if(firstConnect){
        setDeviceMode(deviceMode);
        usbSendControl(0x40, 0xa7, 0, 0, 0, NULL);
        //Stack will reinitialise TIMER_PERIOD seconds later, after first failed iso request
    }

    psuTimer = new QTimer();
    psuTimer->setTimerType(Qt::PreciseTimer);
    psuTimer->start(PSU_PERIOD);
    connect(psuTimer, SIGNAL(timeout()), this, SLOT(psuTick()));
}

unsigned char winUsbDriver::usbInit(ULONG VIDin, ULONG PIDin){
    unsigned char success;

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

void winUsbDriver::usbSendControl(int RequestType, int Request, int Value, int Index, int Length, unsigned char *LDATA){

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

void winUsbDriver::setPsu(double voltage){

    qDebug() << "New voltage =" << voltage;
    currentPsuVoltage = voltage;
    //if(deviceMode > 6) qFatal("setPsu is not configured for mode 7!!!");
    double vinp = voltage/11;
    double vinn = 0;
    //double vref = 1.65;
    double gainPsu = 1;

    dutyPsu = (int) ((vinp - vinn)/vref * gainPsu * PSU_ADC_TOP);

    qDebug() << "Going to send value " << dutyPsu;
}

void winUsbDriver::setFunctionGen(int channel, functionGenControl *fGenControl){
        ////////////////////////////
       ////NO RESIZING (YET)!!!////
      ////////////////////////////

        //////////////////////////////////////
       //// CH1 is AUX!!  CH2 is "MAIN"!!////
      //////////////////////////////////////

    int length, maxLength, numDivides, maxDivides;
    double freq, amplitude, offset;
    unsigned char *samples;

    //For recalling on crash.
    fGenChannel = channel;
    if (channel == 0) fGenPtr_CH1 = fGenControl;
    else fGenPtr_CH2 = fGenControl;

    //Reading in data
    if (channel == 0){
        length = fGenControl->length_CH1;
        freq = fGenControl->freq_CH1;
        amplitude = fGenControl->amplitude_CH1;
        offset = fGenControl->offset_CH1;
        samples = (unsigned char *) malloc(length);
        memcpy(samples, fGenControl->samples_CH1, (unsigned int) length);
        numDivides = fGenControl->divisibility_CH1;
    }
    else if(channel == 1){
        length = fGenControl->length_CH2;
        freq = fGenControl->freq_CH2;
        amplitude = fGenControl->amplitude_CH2;
        offset = fGenControl->offset_CH2;
        samples = (unsigned char *) malloc(length);
        memcpy(samples, fGenControl->samples_CH2, (unsigned int) length);
        numDivides = fGenControl->divisibility_CH2;
    }

    //Triple mode
    if ((amplitude+offset) > FGEN_LIMIT){
        amplitude = amplitude / 3;
        offset = offset / 3;
        fGenTriple |= ((unsigned char) !channel + 1);
    }
    else fGenTriple &= ((unsigned char) (254 - !channel));

    //qDebug() << "fGenTriple = " << fGenTriple << "fGenControl = " << fGenControl << "length = " << length << "freq = " << freq << "amplitude = " << amplitude << "offset = " << offset << "samples = " << samples;

    //Waveform scaling in V
    double tempDouble;
    amplitude = (amplitude * 255) / FGEN_LIMIT;
    offset = (offset * 255) / FGEN_LIMIT;
    if (offset<FGEN_OFFSET){
        if (amplitude>5)
            amplitude -= FGEN_OFFSET;
        else
            amplitude = 0;
        offset = FGEN_OFFSET;
    }

#ifdef INVERT_TRIPLE
    unsigned char fGenTemp = 0;
    fGenTemp |= (fGenTriple & 0x01)<<1;
    fGenTemp |= (fGenTriple & 0x02)>>1;
    usbSendControl(0x40, 0xa4, fGenTemp, 0, 0, NULL);
#else
    usbSendControl(0x40, 0xa4, fGenTriple, 0, 0, NULL);
#endif

    //Applying amplitude and offset to all samples.
    for (int i=0;i<length;i++){
        tempDouble = (double) samples[i];
        tempDouble *= amplitude;
        tempDouble /= 255;
        tempDouble += offset;
        samples[i] = (unsigned char) tempDouble;
    }


    //Need to increase size of wave if its freq too high, or too low!
    maxDivides = numDivides;
    bool loop_entered = false;
    unsigned char *tempSamples = (unsigned char *) malloc(0);

    while(length * freq > DAC_SPS){
        loop_entered = true;
        numDivides--;
        if (numDivides==0){
            qDebug("numDivides = 0 - in T-stretching of winUsbDriver:: setFunctionGen");
        }

        int shiftTemp = (maxDivides - numDivides);
        length = length >> 1;

        free(tempSamples);
        tempSamples = (unsigned char *) malloc(length);
        for (int i=0; i<length;i++){
            tempSamples[i] = samples[i<<shiftTemp];
        }
    }
    if(loop_entered){
        samples = tempSamples;
    }

    //Scaling in t here:
    // Something something maxLength something

    //Timer Setup
    int validClockDivs[7] = {1, 2, 4, 8, 64, 256, 1024};

    int clkSetting;
    for(clkSetting = 0; clkSetting<7; clkSetting++){
        if ( (CLOCK_FREQ / (length * validClockDivs[clkSetting] * freq)) < 65535 )
             break;
    }
    int timerPeriod = CLOCK_FREQ / (length * freq * validClockDivs[clkSetting]);

    clkSetting++;  // Change from [0:n] to [1:n]

    if(deviceMode == 5){
        qDebug("DEVICE IS IN MODE 5");
    }

    //qDebug() << "First three samples:" << samples[0] << samples[1] << samples[2];

    if(channel){
    usbSendControl(0x40, 0xa1, timerPeriod, clkSetting, length, samples);
    }
    else usbSendControl(0x40, 0xa2, timerPeriod, clkSetting, length, samples);
    free(tempSamples);
    return;
}

void winUsbDriver::xmegaBreak(void){
    usbSendControl(0x40, 0xa0, 0, 0, 0, NULL);
}

void winUsbDriver::newDig(int digState){
    qDebug() << "newDig";
    digitalPinState = digState;
    usbSendControl(0x40, 0xa6, digState, 0, 0, NULL);
}

unsigned char winUsbDriver::usbIsoInit(void){
    unsigned char success;
    unsigned int transferred;
    DWORD errorCode = ERROR_SUCCESS;

    success = StmK_Init(
                  &stm_handle,
                  handle,
                  pipeID,
                  MAX_TRANSFER_SIZE,
                  MAX_PENDING_TRANSFERS,
                  MAX_PENDING_IO,
                  NULL,
                  KSTM_FLAG_NONE);
        if (!success){
            errorCode = GetLastError();
            qDebug("StmK_Init failed. ErrorCode: %08Xh\n", errorCode);
            return 0;
        }

        success = StmK_Start(stm_handle);
        if (!success){
            errorCode = GetLastError();
            qDebug("StmK_Start failed. ErrorCode: %08Xh\n", errorCode);
            return 0;
        }

        qDebug("[Start Stream] successful!\n");
        return 1;
}

char *winUsbDriver::isoRead(int numSamples){
    unsigned char *returnBuffer;
    unsigned char success;
    DWORD errorCode = ERROR_SUCCESS;

    returnBuffer = (unsigned char *) malloc(numSamples + 8); //8-byte header contains (unsigned long) length

    success = StmK_Read(stm_handle, returnBuffer+8, 0, numSamples, (PUINT) returnBuffer);
    //qDebug("%d bytes copied, out of a possible %d\n", *((PUINT)returnBuffer), numSamples);
    if (!success)	{
        errorCode = GetLastError();
        qDebug("StmkK_Read failed. ErrorCode: %08Xh\n", errorCode);
        reinitialise(0);
        free(returnBuffer);
        return (char*) malloc(numSamples + 8);
        //printf("No more items = %08Xh\n", ERROR_NO_MORE_ITEMS);
    }

    return (char*) returnBuffer;
}

winUsbDriver::~winUsbDriver(void){
    qDebug() << "\n\nwinUsbDriver destructor ran!";
    unsigned char success;
    DWORD errorCode = ERROR_SUCCESS;

    success = StmK_Stop(stm_handle, 0);
    if (!success)
    {
        errorCode = GetLastError();
        qDebug("StmK_Stop failed. ErrorCode: %08Xh\n", errorCode);
    }
    qDebug("[Stop Stream] successful!\n");

    success = StmK_Free(stm_handle);
    if (!success)
    {
        errorCode = GetLastError();
        qDebug("StmK_Free failed. ErrorCode: %08Xh\n", errorCode);
    }

    UsbK_Free(handle);
}

void winUsbDriver::setBufferPtr(bufferControl *newPtr){
    bufferPtr = newPtr;
}

void winUsbDriver::setDeviceMode(int mode){
    int oldMode = deviceMode;
    deviceMode = mode;
    usbSendControl(0x40, 0xa5, mode, gainMask, 0, NULL);

    if (fGenPtr_CH1!=NULL) setFunctionGen(0, fGenPtr_CH1);
    if (fGenPtr_CH2!=NULL) setFunctionGen(1, fGenPtr_CH2);

    //switch on new deviceMode!!
    switch(deviceMode){
        case 0:
            if(oldMode > 2) sendClearBuffer(1,0,0);
            setVisible_CH2(0);
            checkXY(0);
            break;
        case 1:
            if(oldMode > 2) sendClearBuffer(1,0,0);
            sendClearBuffer(0,1,0);
            setVisible_CH2(1);
            checkXY(0);
            break;
        case 2:
            if(oldMode > 2) sendClearBuffer(1,0,0);
            sendClearBuffer(0,1,0);
            setVisible_CH2(1);
            break;
        case 3:
            if(oldMode != 4) sendClearBuffer(1,0,0);
            sendClearBuffer(0,1,0);
            setVisible_CH2(0);
            checkXY(0);
            break;
        case 4:
            if(oldMode != 3) sendClearBuffer(1,0,0);
            sendClearBuffer(0,1,0);
            setVisible_CH2(1);
            checkXY(0);
            break;
        case 5:
            setVisible_CH2(0);
            checkXY(0);
            break;
        case 6:
            sendClearBuffer(0,0,1);
            setVisible_CH2(0);
            checkXY(0);
            break;
        case 7:
            sendClearBuffer(1,0,0);
            enableMMTimer();
            checkXY(0);
            break;
        default:
            qFatal("Error in winUsbDriver::setDeviceMode.  Invalid device mode.");
    }

}

void winUsbDriver::psuTick(){
    if(dutyTemp == dutyPsu) return;

    if (dutyTemp > dutyPsu){
        if((dutyTemp - dutyPsu)> PSU_STEP){
            dutyTemp -= PSU_STEP;
        } else dutyTemp = dutyPsu;
    }

    if (dutyTemp < dutyPsu){
        if((dutyPsu - dutyTemp)> PSU_STEP){
            dutyTemp += PSU_STEP;
        } else dutyTemp = dutyPsu;
    }

    if ((dutyTemp>113) || (dutyTemp<21)){
        qDebug("PSU DUTY CYCLE TOO LARGE (could underflow on SOF)!!!  ABORTING!!!");
    }
    usbSendControl(0x40, 0xa3, dutyTemp, 0, 0, NULL);
}

void winUsbDriver::setGain(double newGain){
    if (newGain == scopeGain) return; //No update!
    gainBuffers(scopeGain/newGain);
    scopeGain = newGain;
    if (newGain == 0.5){
        gainMask = 7<<2 | 7<<10;
    }
    else gainMask = (unsigned short)(log2(newGain))<<2 | (unsigned short)(log2(newGain))<<10;
    qDebug("newGain = %f", newGain);
    qDebug("gainMask = %d", gainMask);
    usbSendControl(0x40, 0xa5, deviceMode, gainMask, 0, NULL);
}

void winUsbDriver::reinitialise(bool forceAttempt){

    /*if (!firstConnect){
        firstConnect = usbInit(0x03eb, 0xa000);
        setDeviceMode(deviceMode);
        usbIsoInit();
        //Reset!!
        usbSendControl(0x40, 0xa7, 0, 0, 0, NULL);
        //Stack will reinitialise TIMER_PERIOD seconds later, after first failed iso request
        return;
    }*/

    if (!forceAttempt){
        if(recoveryInProcess == true) {
            //qDebug() << "Cancelling reinitialise()";
            return;
        }
    }

    //qDebug() << "reinitialise() entered";

    //if(forceAttempt) qFatal("Forcing attempt");

    disableWindow(0);

    recoveryInProcess = true;

    unsigned char success;
    DWORD errorCode = ERROR_SUCCESS;

    success = UsbK_Free(handle);
    if (!success){
        errorCode = GetLastError();
        qDebug("UsbK_Free (reinit) failed. ErrorCode: %08Xh\n", errorCode);
    }
    //else qDebug() << "Handle freed successfully!";

    if(forceAttempt){
        StmK_Free(stm_handle);
        stm_handle = NULL;
    }
    UsbK_ResetDevice(handle);
    unsigned char initSuccess = usbInit(0x03eb, 0xa000);
    //qDebug() << "usbInit(0x03eb, 0xa000) returned" << initSuccess;

    if (!initSuccess){
        recoverySuccess = 0;
        return;
    }

    setDeviceMode(deviceMode);
    //qDebug() << "setDeviceMode(deviceMode) returned" << deviceSuccess;
    if (fGenPtr_CH1 != NULL) {
        //qDebug() << "setFunctionGen(0, fGenPtr_CH1)";
        setFunctionGen(0, fGenPtr_CH1);
    }
    if (fGenPtr_CH2 != NULL){
        //qDebug() << "setFunctionGen(1, fGenPtr_CH2)";
        setFunctionGen(1, fGenPtr_CH2);
    }
    newDig(digitalPinState);


    unsigned char isoInitSuccess = usbIsoInit();
    //qDebug() << "usbIsoInit() returned" << isoInitSuccess;

    recoverySuccess = initSuccess && isoInitSuccess;

    if(recoverySuccess){
        //qDebug() << "reinitialise() completed successfully";
    }
    //else qDebug() << "reinitialise() completed with errors";
}

void winUsbDriver::avrDebug(void){
    usbSendControl(0x40, 0xa0, 0, 0, 0, NULL);
}
