#ifndef UARTSTYLEDECODER_H
#define UARTSTYLEDECODER_H

#include <QObject>
#include "isobufferbuffer.h"
#include "isobuffer.h"

class uartStyleDecoder : public QObject
{
    Q_OBJECT
public:
    explicit uartStyleDecoder(QObject *parent_in = nullptr);
    void serialDecode(double baudRate);
    int serialDistance();
private:
    isoBuffer *parent;
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
    QTimer *updateTimer;
    QPlainTextEdit *console;

signals:

public slots:
    void updateConsole();
};

#endif // UARTSTYLEDECODER_H
