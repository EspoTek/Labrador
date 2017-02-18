#ifndef ISOBUFFER_H
#define ISOBUFFER_H

#include <QWidget>
#include <QString>
#include <QByteArray>
#include <QDebug>
#include <QTimer>
#include <QPlainTextEdit>
#include <QDir>
#include <QFile>

#include "xmega.h"
#include "desktop_settings.h"
#include "isobufferbuffer.h"

class isoDriver;

//isoBuffer is a generic class that enables O(1) read times (!!!) on all read/write operations, while maintaining a huge buffer size.
//Imagine it as a circular buffer, but with access functions specifically designed for isochronous data from an Xmega.

#define CONSOLE_UPDATE_TIMER_PERIOD 60

class isoBuffer : public QWidget
{
    Q_OBJECT
public:
    isoBuffer(QWidget *parent = 0, int bufferLen = 0, isoDriver *caller = 0, unsigned char channel_value = 0);
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
    QTimer *updateTimer;
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
    isoDriver *virtualParent;
    //Serial Decode
    bool serialDecodingSymbol = false;
    char charBuffer[4096];
    unsigned int charPos = 0;
    unsigned char symbolMax = 7;
    unsigned char symbolCurrent = 0;
    unsigned short symbol = 0;
    char serialPhase = 0;
    isoBufferBuffer *serialBuffer;
    bool symbolUpdated = false;
    //Generic Functions
    void decodeSymbol(unsigned char newBit);
    void marchSerialPtr(int bitPeriod_samples);
    unsigned char numOnes(unsigned short var);
    double sampleConvert(short sample, int TOP, bool AC);
public slots:
    void enableFileIO(QFile *file);
    void disableFileIO();
    void updateConsole();
};

#endif // ISOBUFFER_H
