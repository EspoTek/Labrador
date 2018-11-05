#include "i2cdecoder.h"

using namespace i2c;

i2cDecoder::i2cDecoder(isoBuffer* sda_in, isoBuffer* scl_in) :
	QObject(nullptr),
	sda(sda_in),
    scl(scl_in)
{
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
    {
        qDebug() << "1";
        addressBitStream = (addressBitStream << 1) | 0x0001;
        qDebug("%04x\n", addressBitStream);
    }
    else if (sclEdge == edge::rising && sdaEdge == edge::held_low && currentBitIndex++ < addressBitStreamLength)
    {
        qDebug() << "0";
        addressBitStream = (addressBitStream << 1) & 0xFFFE;
        qDebug("%04x\n", addressBitStream);
    }
    else
        return;

    if (currentBitIndex == addressBitStreamLength)
    {
        qDebug() << "Finished Address Decode";
    }
}

void i2cDecoder::decodeData(edge sdaEdge, edge sclEdge)
{
	// Read in the next bit.
	if(currentBitIndex < 8)
	{	
		if (sdaEdge == edge::rising && sclEdge == edge::held_high)
			currentDataByte |= 0x01;
		else if (sdaEdge == edge::rising && sclEdge == edge::held_low)
			currentDataByte &= 0xFE;
	
		currentDataByte = currentDataByte << 1;
		currentBitIndex++;
	}
	else // Full byte received, check for ACK.
	{
		dataByteCompleted(currentDataByte, sclEdge == edge::held_low);	
		currentBitIndex = 0;
	}
}

void i2cDecoder::startCondition()
{
	currentBitIndex = 0;
    addressBitStream = 0x0000;
	state = transmissionState::address;	
    qDebug() << "I2C START";
}

void i2cDecoder::stopCondition()
{
	switch (state)
	{
		case transmissionState::address:		
			currentBitIndex = 0;
			state = transmissionState::data;
            currentDataByte = 0;
			break;	
		case transmissionState::data:		
            state = transmissionState::idle;
            qDebug() << "Data =" << currentDataByte;
			break;
	}
    qDebug() << "I2C STOP";
}

void i2cDecoder::dataByteCompleted(uint8_t byte, bool ACKed)
{

}
