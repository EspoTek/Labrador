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
    /*
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
    */
}

void isoBuffer::serialDecode(double baudRate)
{
    double dist_seconds = (double)serialDistance()/sampleRate_bit;
    double bitPeriod_seconds = 1/baudRate;

    qDebug() << bitPeriod_seconds;
    qDebug() << dist_seconds;

    return;

    while(dist_seconds > (bitPeriod_seconds + SERIAL_DELAY)){
    }
}

int isoBuffer::serialDistance()
{
    int back_bit = back * 8;
    int bufferEnd_bit = bufferEnd * 8;
    if(back_bit >= serialPtr_bit){
        return back_bit - serialPtr_bit;
    }else return bufferEnd_bit - serialPtr_bit + back_bit;
}
