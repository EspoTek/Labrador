#include "i2cdecoder.h"

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

}
