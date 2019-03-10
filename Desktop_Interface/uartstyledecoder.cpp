#include "uartstyledecoder.h"
#include <QDebug>
#include <cassert>

uartStyleDecoder::uartStyleDecoder(QObject *parent_in)
	: QObject(parent_in)
	, parent{static_cast<isoBuffer*>(parent_in)}
	, m_serialBuffer{SERIAL_BUFFER_LENGTH}
{

	// Begin decoding SAMPLE_DELAY seconds in the past.
	serialPtr_bit = (int)(parent->m_back * 8 - SERIAL_DELAY * parent->m_sampleRate_bit + parent->m_bufferLen * 8) % (parent->m_bufferLen*8);

    updateTimer = new QTimer();
    updateTimer->setTimerType(Qt::PreciseTimer);
    updateTimer->start(CONSOLE_UPDATE_TIMER_PERIOD);
    connect(updateTimer, &QTimer::timeout, this, &uartStyleDecoder::updateConsole);

    if (parent->m_channel == 1)
		console = parent->m_console1;
    else if (parent->m_channel == 2)
		console = parent->m_console2;
    else
		qFatal("Nonexistant console requested in uartStyleDecoder::serialDecode");
}

uartStyleDecoder::~uartStyleDecoder()
{
    std::lock_guard<std::mutex> lock(mutex);
	delete updateTimer;
}

void uartStyleDecoder::updateConsole()
{
	if (!newUartSymbol)
		return;

    std::lock_guard<std::mutex> lock(mutex);

    console->setPlainText(QString::fromLocal8Bit(m_serialBuffer.begin(), m_serialBuffer.size()));
    if (parent->m_serialAutoScroll)
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

void uartStyleDecoder::serialDecode(double baudRate)
{
    /*if(stopDecoding){
        return;
    }*/
    double dist_seconds = (double)serialDistance()/(parent->m_sampleRate_bit);
    double bitPeriod_seconds = 1/baudRate;

    // Used to check for wire disconnects.  You should get at least one "1" for a stop bit.
    bool allZeroes = true;

    while(dist_seconds > (bitPeriod_seconds + SERIAL_DELAY))
	{
        // Read next uart bit
        unsigned char uart_bit = getNextUartBit();

        if (uart_bit == 1)
            allZeroes = false;

        // Process it
        if (uartTransmitting)
        {
            decodeNextUartBit(uart_bit);
        }
        else
        {
            uartTransmitting = uart_bit != 1;  // Uart starts transmitting after start bit (logic low).
            jitterCompensationNeeded = true;
        }

        // Update the pointer, accounting for jitter
        updateSerialPtr(baudRate, uart_bit);
        // Calculate stopping condition
        dist_seconds = (double)serialDistance()/(parent->m_sampleRate_bit);
    }

    //Not a single stop bit, or idle bit, in the whole stream.  Wire must be disconnected.
    if (allZeroes)
	{
        qDebug() << "Wire Disconnect detected!";
        wireDisconnected(parent->m_channel);
        parent->m_isDecoding = false;
        updateTimer->stop();
    }
}

int uartStyleDecoder::serialDistance()
{
    int back_bit = parent->m_back * 8;
    int bufferEnd_bit = (parent->m_bufferLen-1) * 8;
    if (back_bit >= serialPtr_bit)
        return back_bit - serialPtr_bit;
    else
		return bufferEnd_bit - serialPtr_bit + back_bit;
}

void uartStyleDecoder::updateSerialPtr(double baudRate, unsigned char current_bit)
{
    if (jitterCompensationNeeded && uartTransmitting)
        jitterCompensationNeeded = jitterCompensationProcedure(baudRate, current_bit);

    int distance_between_bits = (parent->m_sampleRate_bit)/baudRate;
    if (uartTransmitting)
        serialPtr_bit += distance_between_bits;
	else
		serialPtr_bit += (distance_between_bits - 1);  //Less than one baud period so that it will always see that start bit.

    if (serialPtr_bit >= (parent->m_bufferLen * 8))
        serialPtr_bit -= (parent->m_bufferLen * 8);
}

unsigned char uartStyleDecoder::getNextUartBit()
{
    int coord_byte = serialPtr_bit/8;
    int coord_bit = serialPtr_bit - (8*coord_byte);
    unsigned char dataByte = parent->m_buffer[coord_byte];
    unsigned char mask = (0x01 << coord_bit);
    return ((dataByte & mask) ? 1 : 0);
}

void uartStyleDecoder::decodeNextUartBit(unsigned char bitValue)
{
    if (dataBit_current == parityIndex)
    {
        assert(parity != UartParity::None);
        performParityCheck();
        dataBit_current++;
    }
    else if (dataBit_current < dataBit_max)
    {
        currentUartSymbol |= (bitValue << dataBit_current);
        dataBit_current++;
    }
    else
    {
        decodeDatabit(dataBit_max + 1);
        currentUartSymbol = 0;
        dataBit_current = 0;
        uartTransmitting = false;
        newUartSymbol = true;
    }
}

//This function compensates for jitter by, when the current bit is a "1", and the last bit was a zero, setting the pointer
//to the sample at the midpoint between this bit and the last.
bool uartStyleDecoder::jitterCompensationProcedure(double baudRate, unsigned char current_bit)
{

    //We only run when the current bit is a "1", to prevent slowdown when there are long breaks between transmissions.
    if (current_bit == 0)
        return true;

    //Can't be bothered dealing with the corner case where the serial pointer is at the very start of the buffer.
    //Just return and try again next time.
    int left_coord = serialPtr_bit - (parent->m_sampleRate_bit)/baudRate;
    //qDebug() << "left_coord =" << left_coord;
    if (left_coord < 0)
        return true; //Don't want to read out of bounds!!

    //The usual case, when transmitting anyway.
    unsigned char left_byte = (parent->m_buffer[left_coord/8] & 0xff);
    //Only run when a zero is detected in the leftmost symbol.
    if (left_byte != 255)
	{
        //Step back, one sample at a time, to the 0->1 transition point
        unsigned char temp_bit = 1;
        while(temp_bit)
		{
            temp_bit = getNextUartBit();
            serialPtr_bit--;
        }
        //Jump the pointer forward by half a uart bit period, and return "done!".
        serialPtr_bit += (parent->m_sampleRate_bit/baudRate)/2;
        return false;
    }

    return true;
}

//Basically scaffolding to add character maps for other modes (5 bit, for example).
void uartStyleDecoder::decodeDatabit(int mode)
{
    char tempchar;
    switch(mode)
	{
        case 5:
            tempchar = decode_baudot(currentUartSymbol);
            break;
        case 8:  //8-bit ASCII;
            tempchar = currentUartSymbol;
            break;
        default:
            qDebug() << "uartStyleDecoder::decodeDatabit is failing...";
    }
    if (parityCheckFailed)
    {
        m_serialBuffer.insert("\n<ERROR: Following character contains parity error>\n");
        parityCheckFailed = false;
    }
    m_serialBuffer.insert(tempchar);
}

char uartStyleDecoder::decode_baudot(short symbol)
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

void uartStyleDecoder::performParityCheck()
{
    auto isEvenParity = [=] () -> bool
    {
        uint32_t mask = 0x00000001;
        uint8_t parity = 0;
        for (int i = 0; i < dataBit_max; i++)
        {
            const uint8_t currentBit = (dataBit_current & mask) ? 1 : 0;
            parity = parity ^ currentBit;
            mask = mask << 1;
        }

        return parity == 0;
    };

    switch(parity)
    {
    case UartParity::None:
        assert(false);
        return;
    case UartParity::Even:
        parityCheckFailed = ! isEvenParity();
    case UartParity::Odd:
        parityCheckFailed = isEvenParity();
    }

    return;
}

