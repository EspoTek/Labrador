#include "genericusbdriver.h"

genericUsbDriver::genericUsbDriver(QWidget *parent) : QLabel(parent)
{
    qDebug() << "Making USB Driver invisible!!";
    this->hide();

    //Double buffers are used to send the transfers to isoDriver.  outBuffers and bufferLengths store the actual data from each transfer as well as length.  They are read by isoDriver when it calls isoRead().
    outBuffers[0] = (unsigned char *) calloc(ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX*NUM_ISO_ENDPOINTS + 8, 1);
    outBuffers[1] = (unsigned char *) calloc(ISO_PACKET_SIZE*ISO_PACKETS_PER_CTX*NUM_ISO_ENDPOINTS + 8, 1);
    bufferLengths[0] = 0;
    bufferLengths[1] = 0;

    for(unsigned char k=0; k<NUM_ISO_ENDPOINTS; k++){
        pipeID[k] = 0x81+k;
        qDebug() << "pipeID" << k << "=" << pipeID[k];
    }
}


void genericUsbDriver::setPsu(double voltage){

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

void genericUsbDriver::setFunctionGen(int channel, functionGenControl *fGenControl){
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
            qDebug("numDivides = 0 - in T-stretching of genericUsbDriver:: setFunctionGen");
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

void genericUsbDriver::newDig(int digState){
    qDebug() << "newDig";
    digitalPinState = digState;
    usbSendControl(0x40, 0xa6, digState, 0, 0, NULL);
}

void genericUsbDriver::setBufferPtr(bufferControl *newPtr){
    bufferPtr = newPtr;
}

void genericUsbDriver::setDeviceMode(int mode){
    int oldMode = deviceMode;
    deviceMode = mode;
    usbSendControl(0x40, 0xa5, (mode == 5 ? 0 : mode), gainMask, 0, NULL);

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
            qFatal("Error in genericUsbDriver::setDeviceMode.  Invalid device mode.");
    }

}

void genericUsbDriver::psuTick(){
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

    if ((dutyTemp>106) || (dutyTemp<21)){
        qDebug("PSU DUTY CYCLE of dutyTemp = %d OUT OF RANGE (could underflow on SOF)!!!  ABORTING!!!", dutyTemp);
    }
    usbSendControl(0x40, 0xa3, dutyTemp, 0, 0, NULL);
}

void genericUsbDriver::setGain(double newGain){
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

void genericUsbDriver::avrDebug(void){
    usbSendControl(0xc0, 0xa0, 0, 0, sizeof(unified_debug), NULL);
    unified_debug *udsPtr = (unified_debug *) inBuffer;
    uint16_t trfcnt0 = (udsPtr->trfcntH0 << 8) + udsPtr->trfcntL0;
    uint16_t trfcnt1 = (udsPtr->trfcntH1 << 8) + udsPtr->trfcntL1;
    uint16_t medianTrfcnt = (udsPtr->medianTrfcntH << 8) + udsPtr->medianTrfcntL;
    uint16_t outOfRange = (udsPtr->outOfRangeH << 8) + udsPtr->outOfRangeL;
    uint16_t counter = (udsPtr->counterH << 8) + udsPtr->counterL;
    uint16_t dma_ch0_cnt = (udsPtr->dma_ch0_cntH << 8) + udsPtr->dma_ch0_cntL;
    uint16_t dma_ch1_cnt = (udsPtr->dma_ch1_cntH << 8) + udsPtr->dma_ch1_cntL;


    qDebug("%s", udsPtr->header);
    qDebug() << "trfcnt0 =" << trfcnt0;
    qDebug() << "trfcnt1 =" << trfcnt1;
    qDebug() << "medianTrfcnt =" << medianTrfcnt;
    qDebug() << "outOfRange = " << outOfRange;
    qDebug() << "counter = " << counter;
    qDebug() << "calValNeg = " << udsPtr->calValNeg;
    qDebug() << "calValPos = " << udsPtr->calValPos;
    qDebug() << "CALA = " << udsPtr->CALA;
    qDebug() << "CALB = " << udsPtr->CALB;
    qDebug() << "dma_ch0_cnt = " << dma_ch0_cnt;
    qDebug() << "dma_ch1_cnt = " << dma_ch1_cnt;


}

void genericUsbDriver::saveState(int *_out_deviceMode, double *_out_scopeGain, double *_out_currentPsuVoltage, int *_out_digitalPinState){
    *(_out_deviceMode) = deviceMode;
    *(_out_scopeGain) = scopeGain;
    *(_out_currentPsuVoltage) = currentPsuVoltage;
    *(_out_digitalPinState) = digitalPinState;
    return;
}
