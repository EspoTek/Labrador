#ifndef UARTSTYLEDECODER_H
#define UARTSTYLEDECODER_H

#include <QObject>
#include "isobufferbuffer.h"
#include "isobuffer.h"
#include <mutex>
#include <limits.h>
#include <stdint.h>

enum class UartParity : uint8_t
{
    None,
    Even,
    Odd
};

class uartStyleDecoder : public QObject
{
    Q_OBJECT
public:
    explicit uartStyleDecoder(QObject *parent_in = NULL);
	~uartStyleDecoder();
    void serialDecode(double baudRate);
    int serialDistance();

private:
    isoBuffer *parent;
    int serialPtr_bit;
    bool uartTransmitting = false;
    bool newUartSymbol = false;
    uint32_t dataBit_current = 0;
    uint32_t parityIndex = UINT_MAX;
    uint32_t dataBit_max = 7;
    unsigned short currentUartSymbol = 0;
    bool jitterCompensationNeeded = true;

    void updateSerialPtr(double baudRate, unsigned char current_bit);
    unsigned char getNextUartBit();
    void decodeNextUartBit(unsigned char bitValue);
    bool jitterCompensationProcedure(double baudRate, unsigned char current_bit);

    QPlainTextEdit *console;
    isoBufferBuffer m_serialBuffer;
public:
    QTimer m_updateTimer; // IMPORTANT: must be after m_serialBuffer. construction / destruction order matters

private:
    void decodeDatabit(int mode);
    char decode_baudot(short symbol);

	std::mutex mutex;
    UartParity parity = UartParity::None;

    void performParityCheck();

    bool parityCheckFailed = false;
signals:
    void wireDisconnected(int);
public slots:
    void updateConsole();
    void setParityMode(UartParity newParity);
};

#endif // UARTSTYLEDECODER_H
