#include "i2cdecoder.h"

using namespace i2c;

i2cDecoder::i2cDecoder(isoBuffer* sda_in, isoBuffer* scl_in, QPlainTextEdit* console_in)
    : QObject(nullptr)
    , sda(sda_in)
    , scl(scl_in)
    , console(console_in)
{
    serialBuffer = new isoBufferBuffer(I2C_BUFFER_LENGTH);

    updateTimer = new QTimer();
    updateTimer->setTimerType(Qt::PreciseTimer);
    updateTimer->start(CONSOLE_UPDATE_TIMER_PERIOD);
    connect(updateTimer, &QTimer::timeout, this, &i2cDecoder::updateConsole);
}

i2cDecoder::~i2cDecoder()
{
    // TODO: Is a lock needed here? Destructors should never be called more than once but...
    delete updateTimer;
    delete serialBuffer;
}

void i2cDecoder::reset()
{
    qDebug () << "Resetting I2C";

    if (sda->m_back != scl->m_back)
    {
        // Perhaps the data could be saved, but just resetting them seems much safer
        sda->clearBuffer();
        scl->clearBuffer();
    }

    serialPtr_bit = sda->m_back * 8;

    {
        std::lock_guard<std::mutex> lock(mutex);

        serialBuffer->clear();
    }
}


void i2cDecoder::run()
{
//    qDebug() << "i2cDecoder::run()";
    while (serialDistance(sda) > SERIAL_DELAY * sda->m_sampleRate_bit)
	{
		updateBitValues();
		runStateMachine();
		serialPtr_bit ++;
        if (serialPtr_bit >= (sda->m_bufferLen * 8))
            serialPtr_bit -= (sda->m_bufferLen * 8);
	}	
} 

int i2cDecoder::serialDistance(isoBuffer* buffer)
{
    uint64_t back_bit = buffer->m_back * 8;
    int bufferEnd_bit = buffer->m_bufferLen * 8;
    if (back_bit >= serialPtr_bit)
        return back_bit - serialPtr_bit;
    else
		return bufferEnd_bit - serialPtr_bit + back_bit;
}

void i2cDecoder::updateBitValues(){
    previousSdaValue = currentSdaValue;
    previousSclValue = currentSclValue;

    int coord_byte = serialPtr_bit/8;
    int coord_bit = serialPtr_bit - (8*coord_byte);
    unsigned char dataByteSda = sda->m_buffer[coord_byte];
    unsigned char dataByteScl = scl->m_buffer[coord_byte];
    unsigned char mask = (0x01 << coord_bit);
    currentSdaValue = dataByteSda & mask;
	currentSclValue = dataByteScl & mask;
}

void i2cDecoder::runStateMachine()
{
    edge sdaEdge = edgeDetection(currentSdaValue, previousSdaValue);
	edge sclEdge = edgeDetection(currentSclValue, previousSclValue);

	if ((sdaEdge == edge::rising) && (sclEdge == edge::falling)) // INVALID STATE TRANSITION
	{
        state = transmissionState::unknown;
        qDebug() << "Dumping I2C state and aborting...";
        for (int i=31; i>=0; i--)
            qDebug("%02x\t%02x", sda->m_buffer[serialPtr_bit/8 - i] & 0xFF, scl->m_buffer[serialPtr_bit/8 - i] & 0xFF);
        throw std::runtime_error("unknown i2c transmission state");
        return;
	}

	if ((sdaEdge == edge::rising) && (sclEdge == edge::held_high)) // START
	{
        stopCondition();
		return;
	}

	if ((sdaEdge == edge::falling) && (sclEdge == edge::held_high)) // STOP
	{
        startCondition();
		return;
	}

	switch (state)
	{
		case transmissionState::idle:
			return;
		case transmissionState::address:
			decodeAddress(sdaEdge, sclEdge);
			break;
		case transmissionState::data:
			decodeData(sdaEdge, sclEdge);
			break;		
        case transmissionState::unknown:
        default:
            throw std::runtime_error("State machine is in an invalid state!");
            return;

    }
}

edge i2cDecoder::edgeDetection(uint8_t current, uint8_t prev)
{
	if (current && prev)
		return edge::held_high;
	if (!current && !prev)
		return edge::held_low;
	if (current && !prev)
		return edge::rising;
    if (!current && prev)
		return edge::falling;

    throw std::runtime_error("i2c Edge Detection critical failure");
}

void i2cDecoder::decodeAddress(edge sdaEdge, edge sclEdge)
{
	// Read in the next bit.
    if (sclEdge == edge::rising && sdaEdge == edge::held_high && currentBitIndex++ < addressBitStreamLength)
          currentBitStream = (currentBitStream << 1) | 0x0001;
    else if (sclEdge == edge::rising && sdaEdge == edge::held_low && currentBitIndex++ < addressBitStreamLength)
        currentBitStream = (currentBitStream << 1) & 0xFFFE;
    else
        return;

    if (currentBitIndex == addressBitStreamLength)
    {
        qDebug() << "Finished Address Decode";
        if (currentBitStream & 0b0000000000000010)
            serialBuffer->insert("READ:  ");
        else
            serialBuffer->insert("WRITE: ");

        serialBuffer->insert_hex((uint8_t)((currentBitStream & 0b0000000111111100) >> 2));
        serialBuffer->insert(' ');

        if (currentBitStream & 0b0000000000000001)
            serialBuffer->insert("(NACK)");

        consoleStateInvalid = true;

        // Prepare for next bit
        currentBitIndex = 0;
        currentBitStream = 0x0000;
        state = transmissionState::data;
    }
}

void i2cDecoder::decodeData(edge sdaEdge, edge sclEdge)
{
    // Read in the next bit.
    if (sclEdge == edge::rising && sdaEdge == edge::held_high && currentBitIndex++ < dataBitStreamLength)
          currentBitStream = (currentBitStream << 1) | 0x0001;
    else if (sclEdge == edge::rising && sdaEdge == edge::held_low && currentBitIndex++ < dataBitStreamLength)
        currentBitStream = (currentBitStream << 1) & 0xFFFE;
    else
        return;

    if (currentBitIndex == dataBitStreamLength)
    {
        qDebug() << "Finished Data byte Decode";

        serialBuffer->insert_hex((uint8_t)((currentBitStream & 0b0000000111111110) >> 1));
        serialBuffer->insert(' ');

        if (currentBitStream & 0b0000000000000001)
            serialBuffer->insert("(NACK)");

        consoleStateInvalid = true;

        // Prepare for next bit
        currentBitIndex = 0;
        currentBitStream = 0x0000;
    }
}

void i2cDecoder::startCondition()
{
	currentBitIndex = 0;
    currentBitStream = 0x0000;
	state = transmissionState::address;	
    qDebug() << "I2C START";
}

void i2cDecoder::stopCondition()
{
    state = transmissionState::idle;
    serialBuffer->insert('\n');
    qDebug() << "I2C STOP";
}

void i2cDecoder::updateConsole(){
    std::lock_guard<std::mutex> lock(mutex);
    if (!consoleStateInvalid)
        return;

    console->setPlainText(QString::fromLocal8Bit(serialBuffer->begin(), serialBuffer->size()));
    if(sda->m_serialAutoScroll){
        QTextCursor c =  console->textCursor();
        c.movePosition(QTextCursor::End);
        console->setTextCursor(c);
    }
    consoleStateInvalid = false;
}
