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

#ifndef ISOBUFFER_FILE_H
#define ISOBUFFER_FILE_H

#include <QWidget>
#include "xmega.h"

class isoBuffer_file : public QWidget
{
    Q_OBJECT
public:
    explicit isoBuffer_file(QWidget *parent, int bufferlen, double sampleRate_Hz);

    //Required Functions
    void writeBuffer_float(float* data, int len);
    float *readBuffer(double sampleWindow, int numSamples, bool singleBit, double delayOffset);
    void clearBuffer();
    double samplesPerSecond;
    int bufferEnd, back = 0;
    float *buffer, *readData = NULL;
signals:

public slots:
};

#endif // ISOBUFFER_FILE_H
