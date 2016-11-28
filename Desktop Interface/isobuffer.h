#ifndef ISOBUFFER_H
#define ISOBUFFER_H

#include <QString>
#include <QByteArray>
#include <QDebug>
#include <QTimer>
#include <QPlainTextEdit>
#include <QDir>
#include <QFile>

#include "xmega.h"
#include "desktop_settings.h"

class isoDriver;

//isoBuffer is a generic class that enables O(1) read times (!!!) on all read/write operations, while maintaining a huge buffer size.
//Imagine it as a circular buffer, but with access functions specifically designed for isochronous data from an Xmega.

class isoBuffer
{
public:
    isoBuffer(int bufferLen, isoDriver *caller, unsigned char channel_value);
    //Generic Functions
    void openFile(QString newFile);
    void writeBuffer_char(char *data, int len);
    void writeBuffer_short(short *data, int len);
    short *readBuffer(double sampleWindow, int numSamples, bool singleBit, double delayOffset);
    void clearBuffer();
    void gainBuffer(int gain_log);
    void glitchInsert(short type);
    void serialDecode(double baudRate);
    int serialDistance();
    void serialBegin();
    //Generic Vars
    QPlainTextEdit *console, *console1, *console2;
    bool serialAutoScroll = true;
    unsigned char channel = 255;
private:
    //Generic Vars
    short *buffer, *readData = NULL;
    int bufferEnd, back = 0, serialPtr = 0;
    int samplesPerSecond;
    bool firstTime = true;
    //File I/O
    bool fileIOEnabled = false;
    FILE* fptr = NULL;
    QFile *currentFile;
    isoDriver *parent;
    unsigned int currentColumn = 0;
    //Serial Decode
    bool serialDecodingSymbol = false;
    unsigned char symbolMax = 7;
    unsigned char symbolCurrent = 0;
    unsigned short symbol = 0;
    char serialPhase = 0;
    //Generic Functions
    void decodeSymbol(unsigned char newBit);
    void marchSerialPtr(int bitPeriod_samples);
    unsigned char numOnes(unsigned short var);
    double sampleConvert(short sample, int TOP, bool AC);
public slots:
    void enableFileIO(QFile *file);
    void disableFileIO();

};

#endif // ISOBUFFER_H
