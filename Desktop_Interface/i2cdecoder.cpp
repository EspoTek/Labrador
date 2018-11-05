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
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateConsole()));
}

void i2cDecoder::reset()
{
    qDebug () << "Resetting I2C";

    if (sda->back != scl->back)
    {
        // Perhaps the data could be saved, but just resetting them seems much safer
        sda->clearBuffer();
        scl->clearBuffer();
    }

    serialPtr_bit = sda->back * 8;

    {
        std::lock_guard<std::mutex> lock(mutex);

        delete serialBuffer;
        serialBuffer = new isoBufferBuffer(I2C_BUFFER_LENGTH);
    }
}


void i2cDecoder::run()
{
//    qDebug() << "i2cDecoder::run()";
    while (serialDistance(sda) > SERIAL_DELAY * sda->sampleRate_bit)
	{
		updateBitValues();
		runStateMachine();
		serialPtr_bit ++;
        if (serialPtr_bit > (sda->bufferEnd * 8))
            serialPtr_bit -= (sda->bufferEnd * 8);
	}	
} 

int i2cDecoder::serialDistance(isoBuffer* buffer)
{
    int back_bit = buffer->back * 8;
    int bufferEnd_bit = buffer->bufferEnd * 8;
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
    unsigned char dataByteSda = sda->buffer[coord_byte];
    unsigned char dataByteScl = scl->buffer[coord_byte];
    unsigned char mask = (0x01 << coord_bit);
    currentSdaValue = dataByteSda & mask;
	currentSclValue = dataByteScl & mask;
}

void i2cDecoder::runStateMachine()
{
    edge sdaEdge = edgeDetection(currentSdaValue, previousSdaValue);
	edge sclEdge = edgeDetection(currentSclValue, previousSclValue);

//    if (sdaEdge == edge::rising || sdaEdge == edge::falling)
//        qDebug() << "sdaEdge";
//    if (sclEdge == edge::rising || sclEdge == edge::falling)
//        qDebug() << "sclEdge";

//    if (sclEdge != edge::held_low)
//        qDebug() << "sdaEdge" << (uint8_t)sdaEdge << "sclEdge" << (uint8_t)sclEdge;

	if ((sdaEdge == edge::rising) && (sclEdge == edge::falling)) // INVALID STATE TRANSITION
	{
        state = transmissionState::unknown;
        qDebug() << "Dumping I2C state and aborting...";
        for (int i=31; i>=0; i--)
            qDebug("%02x\t%02x", sda->buffer[serialPtr_bit/8 - i] & 0xFF, scl->buffer[serialPtr_bit/8 - i] & 0xFF);
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
            serialBuffer->add("READ:  ");
        else
            serialBuffer->add("WRITE: ");

        char addressStr[8];
        sprintf(addressStr, "0x%02x ", (currentBitStream & 0b0000000111111100) >> 2);
        serialBuffer->add(addressStr);

        if (currentBitStream & 0b0000000000000001)
            serialBuffer->add("(NACK)");

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

        char dataStr[8];
        sprintf(dataStr, "0x%02x ", (currentBitStream & 0b0000000111111110) >> 1);
        serialBuffer->add(dataStr);

        if (currentBitStream & 0b0000000000000001)
            serialBuffer->add("(NACK)");

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
    serialBuffer->add('\n');
    qDebug() << "I2C STOP";
}

void i2cDecoder::updateConsole(){
    std::lock_guard<std::mutex> lock(mutex);
    if (!consoleStateInvalid)
        return;

    uint32_t numCharsInBuffer = serialBuffer->getNumCharsInBuffer();
    console->setPlainText(QString::fromLocal8Bit(serialBuffer->get(numCharsInBuffer), numCharsInBuffer));
    if(sda->serialAutoScroll){
        QTextCursor c =  console->textCursor();
        c.movePosition(QTextCursor::End);
        console->setTextCursor(c);
    }
    consoleStateInvalid = false;
}
