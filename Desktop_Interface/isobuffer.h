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
#include "genericusbdriver.h"


class isoDriver;

//isoBuffer is a generic class that enables O(1) read times (!!!) on all read/write operations, while maintaining a huge buffer size.
//Imagine it as a circular buffer, but with access functions specifically designed for isochronous data from an Xmega.

#define CONSOLE_UPDATE_TIMER_PERIOD (ISO_PACKETS_PER_CTX * 2)

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
    //Generic Vars
    QPlainTextEdit *console, *console1, *console2;
    bool serialAutoScroll = true;
    unsigned char channel = 255;
    QTimer *updateTimer;
private:
    //Generic Vars
    short *buffer, *readData = NULL;
    int bufferEnd, back = 0;
    int samplesPerSecond, sampleRate_bit;
    bool firstTime = true;
    //File I/O
    bool fileIOEnabled = false;
    FILE* fptr = NULL;
    QFile *currentFile;
    isoDriver *parent;
    unsigned int currentColumn = 0;
    isoDriver *virtualParent;
    //Serial Decode
    int serialPtr_bit = 0;
    bool uartTransmitting = false;
    isoBufferBuffer *serialBuffer;
    bool newUartSymbol = false;
    int dataBit_current = 0, dataBit_max = 7;
    int numCharsInBuffer = 0;
    unsigned short currentUartSymbol = 0;
    bool jitterCompensationNeeded = true;
    void updateSerialPtr(double baudRate, unsigned char current_bit);
    unsigned char getNextUartBit();
    void decodeNextUartBit(unsigned char bitValue);
    bool jitterCompensationProcedure(double baudRate, unsigned char current_bit);
    //Generic Functions
    double sampleConvert(short sample, int TOP, bool AC);
public slots:
    void enableFileIO(QFile *file);
    void disableFileIO();
    void updateConsole();
};

#endif // ISOBUFFER_H
