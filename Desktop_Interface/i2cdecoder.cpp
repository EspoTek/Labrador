#include "i2cdecoder.h"

i2cDecoder::i2cDecoder(isoBuffer* sda_in, isoBuffer* scl_in) : QObject(nullptr)
{
	sda = sda_in;
	scl = scl_in;
}

void i2cDecoder::run()
{

} 

int i2cDecoder::serialDistance(isoBuffer* buffer)
{
    int back_bit = buffer->back * 8;
    int bufferEnd_bit = buffer->bufferEnd * 8;
    if(back_bit >= serialPtr_bit)
        return back_bit - serialPtr_bit;
    else
		return bufferEnd_bit - serialPtr_bit + back_bit;
}
