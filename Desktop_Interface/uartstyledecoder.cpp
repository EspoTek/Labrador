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

#include "uartstyledecoder.h"
#include <QDebug>
#include <cassert>

uartStyleDecoder::uartStyleDecoder(double baudRate, QObject *parent)
	: QObject(parent)
	, m_parent{static_cast<isoBuffer*>(parent)}
	, m_serialBuffer{SERIAL_BUFFER_LENGTH}
	, m_baudRate{baudRate}
{

	// Begin decoding SAMPLE_DELAY seconds in the past.
	serialPtr_bit = (int)(m_parent->m_back * 8 - SERIAL_DELAY * m_parent->m_sampleRate_bit + m_parent->m_bufferLen * 8) % (m_parent->m_bufferLen*8);

    m_updateTimer.setTimerType(Qt::PreciseTimer);
    m_updateTimer.start(CONSOLE_UPDATE_TIMER_PERIOD);
    connect(&m_updateTimer, &QTimer::timeout, this, &uartStyleDecoder::updateConsole);

    if (m_parent->m_channel == 1)
		console = m_parent->m_console1;
    else if (m_parent->m_channel == 2)
		console = m_parent->m_console2;
    else
		qFatal("Nonexistant console requested in uartStyleDecoder::serialDecode");
}

void uartStyleDecoder::updateConsole()
{
	if (!newUartSymbol)
		return;

    std::lock_guard<std::mutex> lock(mutex);

    console->setPlainText(QString::fromLocal8Bit(m_serialBuffer.begin(), m_serialBuffer.size()));
    if (m_parent->m_serialAutoScroll)
	{
        //http://stackoverflow.com/questions/21059678/how-can-i-set-auto-scroll-for-a-qtgui-qtextedit-in-pyqt4   DANKON
        QTextCursor c = console->textCursor();
        c.movePosition(QTextCursor::End);
        console->setTextCursor(c);
        // txtedit.ensureCursorVisible(); // you might need this also
    }
    newUartSymbol = false;
    //charPos = 0;
}

void uartStyleDecoder::serialDecode()
{
    double dist_seconds = (double)serialDistance()/(m_parent->m_sampleRate_bit);
    double bitPeriod_seconds = 1.0 / m_baudRate;

    // Used to check for wire disconnects.  You should get at least one "1" for a stop bit.
    bool allZeroes = true;

    while(dist_seconds > (bitPeriod_seconds + SERIAL_DELAY))
	{
        // Read next uart bit
        bool uart_bit = getNextUartBit();

        if (uart_bit == 1)
            allZeroes = false;

        // Process it
        if (uartTransmitting)
        {
            decodeNextUartBit(uart_bit);
        }
        else
        {
			// Uart starts transmitting after start bit (logic low).
            uartTransmitting = uart_bit == false;
            jitterCompensationNeeded = true;
        }

        // Update the pointer, accounting for jitter
        updateSerialPtr(uart_bit);
        // Calculate stopping condition
        dist_seconds = (double)serialDistance()/(m_parent->m_sampleRate_bit);
    }

    //Not a single stop bit, or idle bit, in the whole stream.  Wire must be disconnected.
    if (allZeroes)
	{
        qDebug() << "Wire Disconnect detected!";
        wireDisconnected(m_parent->m_channel);
        m_parent->m_isDecoding = false;
        m_updateTimer.stop();
    }
}

int uartStyleDecoder::serialDistance() const
{
    int back_bit = m_parent->m_back * 8;
    int bufferEnd_bit = (m_parent->m_bufferLen-1) * 8;
    if (back_bit >= serialPtr_bit)
        return back_bit - serialPtr_bit;
    else
		return bufferEnd_bit - serialPtr_bit + back_bit;
}

void uartStyleDecoder::updateSerialPtr(bool current_bit)
{
    if (jitterCompensationNeeded && uartTransmitting)
        jitterCompensationNeeded = jitterCompensationProcedure(current_bit);

    int distance_between_bits = (m_parent->m_sampleRate_bit)/ m_baudRate;
    if (uartTransmitting)
        serialPtr_bit += distance_between_bits;
	else
		serialPtr_bit += (distance_between_bits - 1);  //Less than one baud period so that it will always see that start bit.

    if (serialPtr_bit >= (m_parent->m_bufferLen * 8))
        serialPtr_bit -= (m_parent->m_bufferLen * 8);
}

bool uartStyleDecoder::getNextUartBit() const
{
	int bitIndex = serialPtr_bit;

    int coord_byte = bitIndex/8;
    int coord_bit = bitIndex - (8*coord_byte);
    uint8_t dataByte = m_parent->m_buffer[coord_byte];
    uint8_t mask = (0x01 << coord_bit);
    return dataByte & mask;
}

void uartStyleDecoder::decodeNextUartBit(bool bitValue)
{
    if (dataBit_current == parityIndex)
    {
        parityCheckFailed = ! isParityCorrect(dataBit_current);
        dataBit_current++;
    }
    else if (dataBit_current < dataBit_max)
    {
        currentUartSymbol |= (bitValue << dataBit_current);
        dataBit_current++;
    }
    else
    {
        char decodedDatabit = decodeDatabit(dataBit_max + 1, currentUartSymbol);

		if (parityCheckFailed)
		{
			m_serialBuffer.insert("\n<ERROR: Following character contains parity error>\n");
			parityCheckFailed = false;
		}

        if (m_hexDisplay)
        {
            m_serialBuffer.insert_hex(decodedDatabit);
            m_serialBuffer.insert(" ");
        }
        else
        {
            m_serialBuffer.insert(decodedDatabit);
        }

        currentUartSymbol = 0;
        dataBit_current = 0;
        uartTransmitting = false;
        newUartSymbol = true;
    }
}

//This function compensates for jitter by, when the current bit is a "1", and the last bit was a zero, setting the pointer
//to the sample at the midpoint between this bit and the last.
bool uartStyleDecoder::jitterCompensationProcedure(bool current_bit)
{

    //We only run when the current bit is a "1", to prevent slowdown when there are long breaks between transmissions.
    if (current_bit == false)
        return true;

    //Can't be bothered dealing with the corner case where the serial pointer is at the very start of the buffer.
    //Just return and try again next time.
    int left_coord = serialPtr_bit - (m_parent->m_sampleRate_bit)/ m_baudRate;
    //qDebug() << "left_coord =" << left_coord;
    if (left_coord < 0)
        return true; //Don't want to read out of bounds!!

    //The usual case, when transmitting anyway.
    uint8_t left_byte = (m_parent->m_buffer[left_coord/8] & 0xff);
    //Only run when a zero is detected in the leftmost symbol.
    if (left_byte != 0xff)
	{
        //Step back, one sample at a time, to the 0->1 transition point
        bool temp_bit = 1;
        while(temp_bit)
		{
            temp_bit = getNextUartBit();
            serialPtr_bit--;
        }
        //Jump the pointer forward by half a uart bit period, and return "done!".
        serialPtr_bit += (m_parent->m_sampleRate_bit/ m_baudRate)/2;
        return false;
    }

    return true;
}

//Basically scaffolding to add character maps for other modes (5 bit, for example).
char uartStyleDecoder::decodeDatabit(int mode, short symbol) const
{
    switch(mode)
	{
        case 5:
            return decodeBaudot(symbol);
            break;
        case 8:  //8-bit ASCII;
            return symbol;
            break;
        default:
            qDebug() << "uartStyleDecoder::decodeDatabit is failing...";
			return -1; // Garbage
    }
}

char uartStyleDecoder::decodeBaudot(short symbol) const
{
    return 'a';
}

void uartStyleDecoder::setParityMode(UartParity newParity)
{
    switch(newParity)
    {
    case UartParity::None:
        parityIndex = UINT_MAX;
        break;
    case UartParity::Even:
    case UartParity::Odd:
        parityIndex = dataBit_max;
    }

    parity = newParity;
}

void uartStyleDecoder::setHexDisplay(bool enabled)
{
    m_hexDisplay = enabled;
}

bool uartStyleDecoder::isParityCorrect(uint32_t bitField) const
{
	assert(parity != UartParity::None);

	return parityOf(bitField) == parity;
}

UartParity uartStyleDecoder::parityOf(uint32_t bitField) const
{
	bool result = false;

	for (uint32_t mask = 1 << (dataBit_max-1); mask != 0; mask >>= 1)
		result ^= static_cast<bool>(bitField & mask);

	return result ? UartParity::Odd : UartParity::Even;
}

