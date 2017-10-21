#include "isobuffer.h"
#include "isodriver.h"


isoBuffer::isoBuffer(QWidget *parent, int bufferLen, isoDriver *caller, unsigned char channel_value) : QWidget(parent)
{
    buffer = (short *) calloc(bufferLen*2, sizeof(short));
    bufferEnd = bufferLen-1;
    samplesPerSecond = (double) bufferLen/(double)21;
    samplesPerSecond = samplesPerSecond/375*VALID_DATA_PER_375;
    sampleRate_bit = samplesPerSecond * 8;
    virtualParent = caller;
    channel = channel_value;

    updateTimer = new QTimer();
    updateTimer->setTimerType(Qt::PreciseTimer);
    updateTimer->start(CONSOLE_UPDATE_TIMER_PERIOD);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateConsole()));

    serialBuffer = new isoBufferBuffer(SERIAL_BUFFER_LENGTH*2);

}
void isoBuffer::openFile(QString newFile)
{
    if (fptr != NULL){
        fclose(fptr);
    }
    if (newFile.isEmpty()){
        fptr = NULL;
    }
    else {
        QByteArray temp = newFile.toLatin1();
        char *fileName = temp.data();
        fptr = fopen(fileName, "w");
        if (fptr == NULL) qFatal("Null fptr in isoBuffer::openFile");
        qDebug() << "opening file" << fileName;
        qDebug() << "fptr = " << fptr;
    }
}

void isoBuffer::writeBuffer_char(char* data, int len)
{
    double convertedSample;
    for (int i=0; i<len;i++){
        //qDebug() << "i = " << i;
        buffer[back] = (short) data[i];
        if (back == bufferEnd){
            back = 0;
            firstTime = false;
        }
        else back++;

        //Output to CSV
        if(fileIOEnabled){
            convertedSample = sampleConvert(data[i], 128, channel==1 ? virtualParent->AC_CH1 : virtualParent->AC_CH2);
            char numStr[32];
            sprintf(numStr,"%f, ", convertedSample);
            currentFile->write(numStr);
            currentColumn++;
            if (currentColumn > COLUMN_BREAK){
                currentFile->write("\n");
                currentColumn = 0;
            }

        }
    }
    return;
}

void isoBuffer::writeBuffer_short(short* data, int len)
{
    //for (int i=(len-1);i>-1;i--){
    for (int i=0; i<len;i++){
        //qDebug() << "i = " << i;
        buffer[back] = (short) data[i] >> 4; //Because it's a left adjust value!
        if (back == bufferEnd){
            back = 0;
            firstTime = false;
        }
        else back++;
    }
    return;
}


short *isoBuffer::readBuffer(double sampleWindow, int numSamples, bool singleBit, double delayOffset)
{
    //ignore singleBit for now
    double timeBetweenSamples = (double) sampleWindow * (double) samplesPerSecond / (double) numSamples;
    double accumulatedDelay = 0;
    int delaySamples = (int)((double)delayOffset * (double)samplesPerSecond);

    int front = back - 1 - delaySamples;
    if (front < 0) front = 0;
    int idx, subIdx;
    if(readData!=NULL) free(readData);
    readData = (short *) calloc(numSamples, sizeof(short));

    if(singleBit){
        for (int i=0; i<numSamples;i++){
            if (timeBetweenSamples > (double) front){
                accumulatedDelay -= (double) front;
                front = bufferEnd;
            }

            idx = (int) floor(((double) front - accumulatedDelay));
            subIdx = (int) floor(8*(((double) front - accumulatedDelay) - floor(((double) front - accumulatedDelay))));

            //qDebug() << "subIdx = " << subIdx;

            if (idx < 0){
                accumulatedDelay--;
                accumulatedDelay -= (double) front;
                front = bufferEnd;
                idx = (int) round(((double) front - accumulatedDelay));
            }
            readData[i] = buffer[idx] & (1<<subIdx);

            accumulatedDelay += timeBetweenSamples;
        }
    }else{
        for (int i=0; i<numSamples;i++){
            if (timeBetweenSamples > (double) front){
                accumulatedDelay -= (double) front;
                front = bufferEnd;
            }

            idx = (int) round(((double) front - accumulatedDelay));
            if (idx < 0){
                accumulatedDelay--;
                accumulatedDelay -= (double) front;
                front = bufferEnd;
                idx = (int) round(((double) front - accumulatedDelay));
            }
            readData[i] = buffer[idx];

            accumulatedDelay += timeBetweenSamples;
        }
    }

    return readData;
}

void isoBuffer::clearBuffer()
{
    for (int i=0; i<bufferEnd;i++){
        buffer[i] = 0;
    }

    back = 0;
    //serialPtr = 0;
    //serialDecodingSymbol = false;
    //symbolCurrent = 0;
    //symbol = 0;

    firstTime = true;
}

void isoBuffer::gainBuffer(int gain_log)
{
    qDebug() << "Buffer shifted by" << gain_log;
    for (int i=0; i<bufferEnd; i++){
        if (gain_log == -1) buffer[i] *= 2;
        else buffer[i] /= 2;
    }
}


void isoBuffer::glitchInsert(short type)
{

}

void isoBuffer::enableFileIO(QFile *file){
    file->open(QIODevice::WriteOnly);
    currentFile = file;
    fileIOEnabled = true;
    return;
}

void isoBuffer::disableFileIO(){
    fileIOEnabled = false;
    currentColumn = 0;
    currentFile->close();
    return;
}

double isoBuffer::sampleConvert(short sample, int TOP, bool AC){

    double scope_gain = (double)(virtualParent->driver->scopeGain);
    double voltageLevel;

    voltageLevel = (sample * (vcc/2)) / (frontendGain*scope_gain*TOP);
    if (virtualParent->driver->deviceMode != 7) voltageLevel += voltage_ref;
    #ifdef INVERT_MM
        if(virtualParent->driver->deviceMode == 7) voltageLevel *= -1;
    #endif

    if(AC){
        voltageLevel -= virtualParent->currentVmean; //This is old (1 frame in past) value and might not be good for signals with large variations in DC level (although the cap should filter that anyway)??
    }
    return voltageLevel;
}

void isoBuffer::updateConsole(){
    if(!newUartSymbol) return;
    qDebug() << numCharsInBuffer;

    console -> setPlainText(QString::fromLocal8Bit(serialBuffer->get(numCharsInBuffer), numCharsInBuffer));
    if(serialAutoScroll){
        //http://stackoverflow.com/questions/21059678/how-can-i-set-auto-scroll-for-a-qtgui-qtextedit-in-pyqt4   DANKON
        QTextCursor c =  console->textCursor();
        c.movePosition(QTextCursor::End);
        console->setTextCursor(c);
        // txtedit.ensureCursorVisible(); // you might need this also
    }
    newUartSymbol = false;
    //charPos = 0;
}

void isoBuffer::serialDecode(double baudRate)
{
    double dist_seconds = (double)serialDistance()/sampleRate_bit;
    double bitPeriod_seconds = 1/baudRate;

    if(channel == 1) console = console1;
    else if(channel == 2) console = console2;
    else qFatal("Nonexistant console requested in isoBuffer::serialDecode");


    while(dist_seconds > (bitPeriod_seconds + SERIAL_DELAY)){
        //Read next uart bit
        unsigned char uart_bit = getNextUartBit();
        //Process it
        if(uartTransmitting){
            decodeNextUartBit(uart_bit);
            //qDebug() << "uart_bit = " << uart_bit;
        } else{
            uartTransmitting = (uart_bit==1) ? false : true;
            jitterCompensationNeeded = true;
            //if(uartTransmitting)  qDebug() << "Decoding symbol!";
        }
        //Update the pointer, accounting for jitter
        updateSerialPtr(baudRate, uart_bit);
        //Calculate stopping condition
        dist_seconds = (double)serialDistance()/sampleRate_bit;
    }
    //qDebug() << "\n\n\n\n\n";
}

int isoBuffer::serialDistance()
{
    int back_bit = back * 8;
    int bufferEnd_bit = bufferEnd * 8;
    if(back_bit >= serialPtr_bit){
        return back_bit - serialPtr_bit;
    }else return bufferEnd_bit - serialPtr_bit + back_bit;
}

void isoBuffer::updateSerialPtr(double baudRate, unsigned char current_bit)
{
    if(jitterCompensationNeeded && uartTransmitting){
        jitterCompensationNeeded = jitterCompensationProcedure(baudRate, current_bit);
        //qDebug() << "JitterCompensation Needed?" << jitterCompensationNeeded;
    }

    int distance_between_bits = sampleRate_bit/baudRate;
    if(uartTransmitting){
        serialPtr_bit += distance_between_bits;
    } else serialPtr_bit += (distance_between_bits - 1);  //Less than one baud period so that it will always see that start bit.

    if (serialPtr_bit > (bufferEnd * 8)){
        serialPtr_bit -= (bufferEnd * 8);
    }
}

unsigned char isoBuffer::getNextUartBit(){
    int coord_byte = serialPtr_bit/8;
    int coord_bit = serialPtr_bit - (8*coord_byte);
    unsigned char dataByte = buffer[coord_byte];
    unsigned char mask = (1 << coord_bit);
    return ((dataByte & mask) ? 1 : 0);
}

void isoBuffer::decodeNextUartBit(unsigned char bitValue)
{
    if(dataBit_current == dataBit_max){
        if(numCharsInBuffer<SERIAL_BUFFER_LENGTH) numCharsInBuffer++;
        serialBuffer->add(currentUartSymbol);
        currentUartSymbol = 0;
        dataBit_current = 0;
        uartTransmitting = false;
        newUartSymbol = true;
        return;
    }
    //else
    currentUartSymbol |= (bitValue << dataBit_current);
    dataBit_current++;
}

bool isoBuffer::jitterCompensationProcedure(double baudRate, unsigned char current_bit){

    if(current_bit !=0){
        //qDebug() << "Current bit not zero!!";
        return true;
    }

    int left_coord = serialPtr_bit - sampleRate_bit/baudRate;
    if (left_coord < 0){
        return true; //Don't want to read out of bounds!!
    }

    unsigned char left_byte = (buffer[left_coord/8] & 0xff);
    //qDebug() << "current_bit" << current_bit;
    //qDebug() << "left_byte" << left_byte;

    if(left_byte > 0){
        //qDebug() << "Recalibration Opportunity";
        unsigned char temp_bit = 0;
        //Go back to 1-0 transition point
        while(!temp_bit){
            temp_bit = getNextUartBit();
            serialPtr_bit--;
        }
        //Jump by half a uart bit period.
        serialPtr_bit += (sampleRate_bit/baudRate)/2;
        return false;
    }

    return true;
}

short isoBuffer::inverseSampleConvert(double voltageLevel, int TOP, bool AC){

    double scope_gain = (double)(virtualParent->driver->scopeGain);
    short sample;

    if(AC){
        voltageLevel += virtualParent->currentVmean; //This is old (1 frame in past) value and might not be good for signals with large variations in DC level (although the cap should filter that anyway)??
    }
#ifdef INVERT_MM
    if(virtualParent->driver->deviceMode == 7) voltageLevel *= -1;
#endif
    if (virtualParent->driver->deviceMode != 7) voltageLevel -= voltage_ref;

    //voltageLevel = (sample * (vcc/2)) / (frontendGain*scope_gain*TOP);
    sample = (voltageLevel * (frontendGain*scope_gain*TOP))/(vcc/2);
    return sample;
}

#define NUM_SAMPLES_SEEKING_CAP (20)

#ifdef INVERT_MM
    #define X0_COMPARISON_CAP >
    #define X1_X2_COMPARISON_CAP <
#else
    #define X0_COMPARISON_CAP <
    #define X1_X2_COMPARISON_CAP >
#endif


int isoBuffer::cap_x0fromLast(double seconds, double vbot){
    int samplesInPast = seconds * samplesPerSecond;
    if(back < samplesInPast){
        return -1; //too hard, not really important
    }
    short vbot_s = inverseSampleConvert(vbot, 2048, 0);
    qDebug() << "vbot_s (x0) = " << vbot_s;

    int num_found = 0;
    for(int i=samplesInPast; i; i--){
        short currentSample = buffer[back - i];
        if(currentSample X0_COMPARISON_CAP vbot_s){
            num_found++;
        } else num_found--;
        if(num_found < 0){
            num_found = 0;
        }
        if (num_found > NUM_SAMPLES_SEEKING_CAP){
            return samplesInPast-i;
        }
    }
    return -1;
}

int isoBuffer::cap_x1fromLast(double seconds, int x0, double vbot){
    int samplesInPast = seconds * samplesPerSecond;
    samplesInPast -= x0;
    if(back < samplesInPast){
        return -1; //too hard, not really important
    }
    short vbot_s = inverseSampleConvert(vbot, 2048, 0);
    qDebug() << "vbot_s (x1) = " << vbot_s;

    int num_found = 0;
    for(int i=samplesInPast; i; i--){
        short currentSample = buffer[back - i];
        if(currentSample X1_X2_COMPARISON_CAP vbot_s){
            num_found++;
        } else num_found--;
        if(num_found < 0){
            num_found = 0;
        }
        if (num_found > NUM_SAMPLES_SEEKING_CAP){
            return samplesInPast-i + x0;
        }

    }
    return -1;
}

int isoBuffer::cap_x2fromLast(double seconds, int x1, double vtop){
    int samplesInPast = seconds * samplesPerSecond;
    samplesInPast -= x1;
    if(back < samplesInPast){
        return -1; //too hard, not really important
    }
    short vtop_s = inverseSampleConvert(vtop, 2048, 0);
    qDebug() << "vtop_s (x2) = " << vtop_s;

    int num_found = 0;
    for(int i=samplesInPast; i; i--){
        short currentSample = buffer[back - i];
        if(currentSample X1_X2_COMPARISON_CAP vtop_s){
            num_found++;
        } else num_found--;
        if(num_found < 0){
            num_found = 0;
        }
        if (num_found > NUM_SAMPLES_SEEKING_CAP){
            return samplesInPast-i + x1;
        }
    }
    return -1;
}




