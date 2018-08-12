#include "i2cdecoder.h"

using namespace i2c;

i2cDecoder::i2cDecoder(isoBuffer* sda_in, isoBuffer* scl_in, uint32_t clockRate) : QObject(nullptr)
{
	sda = sda_in;
	scl = scl_in;
	setStepSize(clockRate);
}

void i2cDecoder::run()
{
	while (serialDistance(sda) > SERIAL_DELAY * sda->sampleRate_bit)
	{
		updateBitValues();
		runStateMachine();
		serialPtr_bit += stepSize;
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
    int coord_byte = serialPtr_bit/8;
    int coord_bit = serialPtr_bit - (8*coord_byte);
    unsigned char dataByteSda = sda->buffer[coord_byte];
    unsigned char dataByteScl = scl->buffer[coord_byte];
    unsigned char mask = (1 << coord_bit);
	currentSdaValue = dataByteSda & mask;
	currentSclValue = dataByteScl & mask;
}

void i2cDecoder::setStepSize(uint32_t clockRate)
{
	stepSize = (double)((sda->sampleRate_bit)/clockRate)/2.0;
	if (stepSize > (SERIAL_DELAY * sda->sampleRate_bit)/2)
		stepSize = SERIAL_DELAY * sda->sampleRate_bit / 2;
}

void i2cDecoder::runStateMachine()
{
	edge sdaEdge = edgeDetection(currentSdaValue, previousSdaValue);
	edge sclEdge = edgeDetection(currentSclValue, previousSclValue);
		
	if ((sdaEdge == edge::rising) && (sclEdge == edge::falling)) // INVALID STATE TRANSITION
	{
		state = transmissionState::unknown;	
		return;
	}

	if ((sdaEdge == edge::rising) && (sclEdge == edge::held_high)) // START
	{
		startCondition();
		return;
	}

	if ((sdaEdge == edge::falling) && (sclEdge == edge::held_high)) // STOP
	{
		stopCondition();
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
	if (!current &&!prev)
		return edge::falling;
}

void i2cDecoder::decodeAddress(edge sdaEdge, edge sclEdge)
{
	// Read in the next bit.
	if (sdaEdge == edge::rising && sclEdge == edge::held_high)
		address |= 0x0001;
	else if (sdaEdge == edge::rising && sclEdge == edge::held_low)
		address &= 0xFFFE;
	
	address = address << 1;
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
	address = 0x0000;
	state = transmissionState::address;	
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
			break;
	}
}

void i2cDecoder::dataByteCompleted(uint8_t byte, bool ACKed)
{

}
