#include "isobuffer.h"
#include "isodriver.h"

#include "uartstyledecoder.h"

isoBuffer::isoBuffer(QWidget *parent, int bufferLen, isoDriver *caller, unsigned char channel_value) : QWidget(parent)
{
    buffer = (short *) calloc(bufferLen*2, sizeof(short));
    bufferEnd = bufferLen-1;
    samplesPerSecond = (double) bufferLen/(double)21;
    samplesPerSecond = samplesPerSecond/375*VALID_DATA_PER_375;
    sampleRate_bit = samplesPerSecond * 8;
    virtualParent = caller;
    channel = channel_value;
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
            //Current sample
            convertedSample = sampleConvert(data[i], 128, channel==1 ? virtualParent->AC_CH1 : virtualParent->AC_CH2);

            //Accumulate
            average_sample_temp += convertedSample;
            fileIO_sampleCount++;
            //Check to see if we can write a new sample to file
            if(fileIO_sampleCount == fileIO_maxIncrementedSampleValue){
                char numStr[32];
                sprintf(numStr,"%7.5f, ", average_sample_temp/((double)fileIO_maxIncrementedSampleValue));
                currentFile->write(numStr);
                currentColumn++;
                if (currentColumn >= COLUMN_BREAK){
                    currentFile->write("\n");
                    currentColumn = 0;
                }

                //Reset the average and sample count for next data point
                fileIO_sampleCount = 0;
                average_sample_temp = 0;

                //Check to see if we've reached the max file size.
                if(fileIO_max_file_size != 0){ //value of 0 means "no limit"
                    fileIO_numBytesWritten += 9;  //7 chars for the number, 1 for the comma and 1 for the space = 9 bytes per sample.
                    if(fileIO_numBytesWritten >= fileIO_max_file_size){
                        fileIOEnabled = false; //Just in case signalling fails.
                        fileIOinternalDisable();
                    }
                }
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


        double convertedSample;
        //Output to CSV
        if(fileIOEnabled){
            //Current sample
            convertedSample = sampleConvert((data[i] >> 4), 2048, channel==1 ? virtualParent->AC_CH1 : virtualParent->AC_CH2);

            //Accumulate
            average_sample_temp += convertedSample;
            fileIO_sampleCount++;
            //Check to see if we can write a new sample to file
            if(fileIO_sampleCount == fileIO_maxIncrementedSampleValue){
                char numStr[32];
                sprintf(numStr,"%7.5f, ", average_sample_temp/((double)fileIO_maxIncrementedSampleValue));
                currentFile->write(numStr);
                currentColumn++;
                if (currentColumn >= COLUMN_BREAK){
                    currentFile->write("\n");
                    currentColumn = 0;
                }

                //Reset the average and sample count for next data point
                fileIO_sampleCount = 0;
                average_sample_temp = 0;

                //Check to see if we've reached the max file size.
                if(fileIO_max_file_size != 0){ //value of 0 means "no limit"
                    fileIO_numBytesWritten += 9;  //7 chars for the number, 1 for the comma and 1 for the space = 9 bytes per sample.
                    if(fileIO_numBytesWritten >= fileIO_max_file_size){
                        fileIOEnabled = false; //Just in case signalling fails.
                        fileIOinternalDisable();
                    }
                }
            }
        }
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

void isoBuffer::enableFileIO(QFile *file, int samplesToAverage, qulonglong max_file_size){

    //Open the file
    file->open(QIODevice::WriteOnly);
    currentFile = file;

    //Add the header
    char headerLine[256];
    sprintf(headerLine, "EspoTek Labrador DAQ V1.0 Output File\nAveraging = %d\nMode = %d\n", samplesToAverage, virtualParent->driver->deviceMode);
    currentFile->write(headerLine);

    //Set up the isoBuffer for DAQ
    fileIO_maxIncrementedSampleValue = samplesToAverage;
    fileIO_max_file_size = max_file_size;
    fileIO_sampleCount = 0;
    fileIO_numBytesWritten = 0;
    average_sample_temp = 0;

    //Enable DAQ
    fileIOEnabled = true;

    qDebug("File IO enabled, averaging %d samples, max file size %uMB", samplesToAverage, max_file_size/1000000);
    qDebug() << max_file_size;
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

void isoBuffer::serialManage(double baudRate, int type){
    //Types:
    // 0 - standard UART, no parity
    // 1 - standard UART, with parity bit
    // 100 - I2C
    if(decoder == NULL){
        decoder = new uartStyleDecoder(this);
        connect(decoder, SIGNAL(wireDisconnected(int)), virtualParent, SLOT(serialNeedsDisabling(int)));
    }
    if(stopDecoding){
        decoder->updateTimer->start(CONSOLE_UPDATE_TIMER_PERIOD);
        stopDecoding = false;
    }
    decoder->serialDecode(baudRate);
}




