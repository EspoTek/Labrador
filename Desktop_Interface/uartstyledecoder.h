#ifndef UARTSTYLEDECODER_H
#define UARTSTYLEDECODER_H

#include <QObject>
#include "isobufferbuffer.h"
#include "isobuffer.h"
#include <mutex>

class uartStyleDecoder : public QObject
{
    Q_OBJECT
public:
    explicit uartStyleDecoder(QObject *parent_in = NULL);
	~uartStyleDecoder();
    void serialDecode(double baudRate);
    int serialDistance();
    QTimer *updateTimer;
private:
    isoBuffer *parent;
    int serialPtr_bit;
    bool uartTransmitting = false;
    bool newUartSymbol = false;
    int dataBit_current = 0, dataBit_max = 7;
    unsigned short currentUartSymbol = 0;
    bool jitterCompensationNeeded = true;
    void updateSerialPtr(double baudRate, unsigned char current_bit);
    unsigned char getNextUartBit();
    void decodeNextUartBit(unsigned char bitValue);
    bool jitterCompensationProcedure(double baudRate, unsigned char current_bit);
    QPlainTextEdit *console;
    isoBufferBuffer *serialBuffer;
    int numCharsInBuffer = 0;
    void decodeDatabit(int mode);
    char decode_baudot(short symbol);
	std::mutex mutex;
signals:
    void wireDisconnected(int);
public slots:
    void updateConsole();
};

#endif // UARTSTYLEDECODER_H
