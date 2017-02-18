#include "isobuffer.h"
#include "isodriver.h"


isoBuffer::isoBuffer(QWidget *parent, int bufferLen, isoDriver *caller, unsigned char channel_value) : QWidget(parent)
{
    buffer = (short *) calloc(bufferLen*2, sizeof(short));
    bufferEnd = bufferLen-1;
    samplesPerSecond = (double) bufferLen/(double)21;
    samplesPerSecond = samplesPerSecond/375*VALID_DATA_PER_375;
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
    serialPtr = 0;
    serialDecodingSymbol = false;
    symbolCurrent = 0;
    symbol = 0;

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

void isoBuffer::serialDecode(double baudRate)
{
    double dist_seconds = (double)serialDistance()/samplesPerSecond;
    double bitPeriod_seconds = 1/baudRate;
    unsigned short* tempPtr;
    unsigned short tempShort;
    unsigned char tempChar;

    if(channel == 1) console = console1;
    else if(channel == 2) console = console2;
    else qFatal("Nonexistant console requested in isoBuffer::serialDecode");

    while(dist_seconds > (bitPeriod_seconds + SERIAL_DELAY)){
        tempPtr = (unsigned short *) readBuffer(0, 1, false, dist_seconds - bitPeriod_seconds);
        tempShort = *(tempPtr);
        tempShort = tempShort & 0xff;
        tempChar = tempShort & (1 << serialPhase) ? 0 : 1;
        if(serialDecodingSymbol){
            //if((tempShort != 0) && (tempShort!= 255)) qDebug() << "tempShort = " << tempShort;
            //qDebug() << numOnes(tempShort);
            decodeSymbol(numOnes(tempShort) > 4);
        }
        else serialDecodingSymbol = (numOnes(tempShort) < 8);
        marchSerialPtr(bitPeriod_seconds * samplesPerSecond);
        dist_seconds = (double)serialDistance()/samplesPerSecond;
    }
}

int isoBuffer::serialDistance()
{
    if(back >= serialPtr){
        return back - serialPtr;
    }else return bufferEnd - serialPtr + back;
}

void isoBuffer::serialBegin()
{
    serialPtr = back;
}


void isoBuffer::decodeSymbol(unsigned char newBit) //Slow but works.
{
    if(symbolCurrent == symbolMax){  //Last bit in symbol
        //charBuffer[charPos] = symbol;
        if(charPos<SERIAL_BUFFER_LENGTH) charPos++;
        serialBuffer->add(symbol);
        symbolCurrent++;
        symbolUpdated = true;
        return;
    }
    if(symbolCurrent > symbolMax){  //Wait for stop bit.  Stops over the top calculation when you get a string of zeroes...
        if(newBit == 1){
            serialDecodingSymbol = false;
            symbolCurrent = 0;
            symbol = 0;
        }
        return;
    }
    //otherwise
        symbol |= newBit << symbolCurrent;
        symbolCurrent++;
}

void isoBuffer::marchSerialPtr(int bitPeriod_samples)
{
    int halfPeriod = bitPeriod_samples * 0.6;
    int sampleDistance = -1;

    serialPtr += bitPeriod_samples;
    if(serialPtr >= bufferEnd){
        serialPtr -= bufferEnd;
    }
    if(!serialDecodingSymbol){
        return;
    }

    if((serialPtr <= halfPeriod) || (serialPtr > (bufferEnd - halfPeriod))) return;  //Don't bother readjusting.  Too hard.

    //otherwise...
    if(buffer[serialPtr] != buffer[serialPtr - halfPeriod]){ //use LHS to calibrate
        for (int i=halfPeriod;i>=0;i--){
            if(buffer[serialPtr] == buffer[serialPtr-i]){
                sampleDistance = i;
                break;
            }
        }
        if(sampleDistance != -1) serialPtr += (bitPeriod_samples/2) - sampleDistance;
    }

    if(sampleDistance == -1){
        if(buffer[serialPtr] != buffer[serialPtr + halfPeriod]){ //same as above but with RHS
            for (int i=halfPeriod;i>=0;i--){
                if(buffer[serialPtr] == buffer[serialPtr+i]){
                    sampleDistance = i;
                    break;
                }
            }
            if(sampleDistance != -1) serialPtr -= (bitPeriod_samples/2) - sampleDistance;
        }
    }
}

unsigned char isoBuffer::numOnes(unsigned short var){
    return ((var&0x01) ? 1 : 0) + ((var&0x02) ? 1 : 0) + ((var&0x04) ? 1 : 0) + ((var&0x08) ? 1 : 0) + ((var&0x10) ? 1 : 0) + ((var&0x20) ? 1 : 0) + ((var&0x40) ? 1 : 0) + ((var&0x80) ? 1 : 0);
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

    voltageLevel = (sample * (vcc/2)) / (R4/(R3+R4)*scope_gain*TOP);
    if (virtualParent->driver->deviceMode != 7) voltageLevel += vcc*(R2/(R1+R2));
    #ifdef INVERT_MM
        if(virtualParent->driver->deviceMode == 7) voltageLevel *= -1;
    #endif

    if(AC){
        voltageLevel -= virtualParent->currentVmean; //This is old (1 frame in past) value and might not be good for signals with large variations in DC level (although the cap should filter that anyway)??
    }
    return voltageLevel;
}

void isoBuffer::updateConsole(){
    if(!symbolUpdated) return;
    qDebug() << charPos;

    console -> setPlainText(QString::fromLocal8Bit(serialBuffer->get(charPos), charPos));
    if(serialAutoScroll){
        //http://stackoverflow.com/questions/21059678/how-can-i-set-auto-scroll-for-a-qtgui-qtextedit-in-pyqt4   DANKON
        QTextCursor c =  console->textCursor();
        c.movePosition(QTextCursor::End);
        console->setTextCursor(c);
        // txtedit.ensureCursorVisible(); // you might need this also
    }
    symbolUpdated = false;
    //charPos = 0;
}

