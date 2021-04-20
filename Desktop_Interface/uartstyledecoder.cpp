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
        emit wireDisconnected(m_parent->m_channel);
        m_parent->m_isDecoding = false;
        m_updateTimer.stop();
    }
}

int uartStyleDecoder::serialDistance() const
{
    unsigned back_bit = m_parent->m_back * 8;
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
        bool temp_bit = true;
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
char uartStyleDecoder::decodeDatabit(int mode, short symbol)
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

char uartStyleDecoder::decodeBaudot(short symbol)
{
    // Baudot-Murray code, ITA2 variant

    if (m_baudotFigures) {
        switch(symbol) {
        case 1: return '3';
        case 3: return '-';
        case 5: return '\'';
        case 6: return '8';
        case 7: return '7';
        case 9: return 0x5; // Enquiry
        case 11: return '\a'; // Bell
        case 12: return ',';
        case 13: return '!';
        case 14: return ':';
        case 15: return '(';
        case 16: return '5';
        case 17: return '+';
        case 18: return ')';
        case 19: return '2';
        case 20: return '$'; // or £
        case 21: return '6';
        case 22: return '0';
        case 23: return '1';
        case 24: return '9';
        case 25: return '?';
        case 26: return '&'; // or @
        case 28: return '.';
        case 29: return '/';
        case 30: return ';';

        case 27: return ' '; // Switch to figures in letter mode
        case 31: m_baudotFigures = false; return -1; // Switch to letters

        default:
            // Either a common one, or unknown
            break;
        }
    }

    // Letter mode:
    switch(symbol) {
    case 0: return '\0';
    case 2:  return '\n';
    case 8:  return '\r';

    case 1: return 'E';
    case 3: return 'A';
    case 4: return ' ';
    case 5: return 'S';
    case 6: return 'I';
    case 7: return 'U';
    case 9: return 'D';
    case 10: return 'R';
    case 11: return 'J';
    case 12: return 'N';
    case 13: return 'F';
    case 14: return 'C';
    case 15: return 'K';
    case 16: return 'T';
    case 17: return 'Z';
    case 18: return 'L';
    case 19: return 'W';
    case 20: return 'H';
    case 21: return 'Y';
    case 22: return 'P';
    case 23: return 'Q';
    case 24: return 'O';
    case 25: return 'B';
    case 26: return 'G';
    case 28: return 'M';
    case 29: return 'X';
    case 30: return 'V';

    case 27: m_baudotFigures = true; return ' ';
    case 31: return 0x8; // Delete/erase, we return backspace
    default:
        qWarning() << "Invalid baudot:" << symbol;
        return -1;
    }
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

