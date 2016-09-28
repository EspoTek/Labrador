#ifndef ISOBUFFER_H
#define ISOBUFFER_H

#include <QString>
#include <QByteArray>
#include <QDebug>
#include <QTimer>
#include "xmega.h"
#include "desktop_settings.h"
#include <QPlainTextEdit>
#include <Qdir>
#include <QFile>

class isoDriver;

class isoBuffer
{
public:
    isoBuffer(int bufferLen, isoDriver *caller, unsigned char channel_value);
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
    QPlainTextEdit *console, *console1, *console2;
    bool serialAutoScroll = true;
    unsigned char channel = 255;
private:
    short *buffer, *readData = NULL;
    FILE* fptr = NULL;
    int bufferEnd, back = 0, serialPtr = 0;
    int samplesPerSecond;
    bool firstTime = true;
    bool serialDecodingSymbol = false;
    unsigned char symbolMax = 7;
    unsigned char symbolCurrent = 0;
    unsigned short symbol = 0;
    void decodeSymbol(unsigned char newBit);
    void marchSerialPtr(int bitPeriod_samples);
    char serialPhase = 0;
    unsigned char numOnes(unsigned short var);
    QFile *currentFile;
    bool fileIOEnabled = false;
    unsigned int currentColumn = 0;
    isoDriver *parent;
    double sampleConvert(short sample, int TOP, bool AC);
public slots:
    void enableFileIO(QFile *file);
    void disableFileIO();

};

#endif // ISOBUFFER_H
