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
    explicit uartStyleDecoder(double baudRate, QObject *parent = NULL);
	~uartStyleDecoder() = default;


private:
    isoBuffer *m_parent;

	// Indicates the current bit being decoded.
    int serialPtr_bit;

    bool uartTransmitting = false;
    bool newUartSymbol = false;
    uint32_t dataBit_current = 0;
    uint32_t parityIndex = UINT_MAX;
    uint32_t dataBit_max = 7;
    unsigned short currentUartSymbol = 0;
    bool jitterCompensationNeeded = true;

    void updateSerialPtr(bool current_bit);
    bool getNextUartBit() const;
    void decodeNextUartBit(bool bitValue);
    bool jitterCompensationProcedure(bool current_bit);

    bool m_hexDisplay = false;

    QPlainTextEdit *console;
    isoBufferBuffer m_serialBuffer;
public:
	double m_baudRate;
    QTimer m_updateTimer; // IMPORTANT: must be after m_serialBuffer. construction / destruction order matters
    void serialDecode();
    int serialDistance() const;

signals:
    void wireDisconnected(int);

public slots:
    void updateConsole();
    void setParityMode(UartParity newParity);
    void setHexDisplay(bool enabled);

private:
    char decodeDatabit(int mode, short symbol) const;
    char decodeBaudot(short symbol) const;

	std::mutex mutex;
    UartParity parity = UartParity::None;

    bool isParityCorrect(uint32_t bitField) const;
	UartParity parityOf(uint32_t bitField) const;

    bool parityCheckFailed = false;

};

#endif // UARTSTYLEDECODER_H
