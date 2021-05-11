// Copyright (C) 2017, 2018, 2019, 2020, 2021 Christopher Paul Esposito
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "isobuffer_file.h"
#include "math.h"
#include <QDebug>

isoBuffer_file::isoBuffer_file(QWidget *parent, int bufferlen, double sampleRate_Hz) : QWidget(parent)
{
    buffer = (float *) calloc(bufferlen, sizeof(float));
    bufferEnd = bufferlen-1;
    samplesPerSecond = sampleRate_Hz;
}

void isoBuffer_file::writeBuffer_float(float* data, int len)
{
    for (int i=0; i<len;i++){
        buffer[back] = (float) data[i];
        if (back == bufferEnd){
            back = 0;
        }
        else back++;
    }
    return;
}

float *isoBuffer_file::readBuffer(double sampleWindow, int numSamples, bool singleBit, double delayOffset)
{
    //ignore singleBit for now
    double timeBetweenSamples = (double) sampleWindow * samplesPerSecond / (double) numSamples;
    double accumulatedDelay = 0;
    int delaySamples = (int)((double)delayOffset * samplesPerSecond);

    int front = back - 1 - delaySamples;
    if (front < 0) front = 0;
/*
    qDebug() << "sampleWindow" << sampleWindow;
    qDebug() << "numSamples" << numSamples;
    qDebug() << "delayOffset" << delayOffset;
    qDebug() << "samplesPerSecond" << samplesPerSecond;
    qDebug() << "timeBetweenSamples" << timeBetweenSamples;
    qDebug() << "delaySamples" << delaySamples;
    qDebug() << "back" << back;
    qDebug() << "front" << front;
*/
    int idx, subIdx;
    if(readData!=NULL) free(readData);
    readData = (float *) calloc(numSamples, sizeof(float));


    if(singleBit){
        return readData; //Garbage.  Not supported.
    }else{
        for (int i=0; i<numSamples;i++){
            if (timeBetweenSamples > (double) front){
                qDebug() << "Wrap!";
                accumulatedDelay -= (double) front;
                front = bufferEnd;
            }

            idx = (int) round(((double) front - accumulatedDelay));
            if (idx < 0){
                qDebug() << "Wrap";
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

void isoBuffer_file::clearBuffer()
{
    for (int i=0; i<bufferEnd;i++){
        buffer[i] = 0;
    }

    back = 0;
}

