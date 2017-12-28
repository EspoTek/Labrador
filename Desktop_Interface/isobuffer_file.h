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
