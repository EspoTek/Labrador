#include "isobufferbuffer.h"

isoBufferBuffer::isoBufferBuffer(uint32_t length)
    : bufferLength(length)
{
    mid = bufferLength/2;
    buffer = (char *) malloc((bufferLength * 3) / 2);
}

void isoBufferBuffer::add(std::string newString)
{
    for (char& newChar : newString)
        add(newChar);
}


void isoBufferBuffer::add(char newChar){
    buffer[ptr] = newChar;

    if(ptr < mid)
        buffer[ptr + bufferLength] = newChar;

    if (ptr >= bufferLength)
        ptr = 0;
    else ptr++;

    numCharsInBuffer = std::min(numCharsInBuffer + 1, mid);
}

uint32_t isoBufferBuffer::getNumCharsInBuffer()
{
    return numCharsInBuffer;
}

char *isoBufferBuffer::get(uint32_t length){
    if (length > mid)
        qFatal("isoBuffer::get; length requested is too high.");
    if(ptr < mid)
        return &buffer[ptr + bufferLength - length];
    else
        return &buffer[ptr - length];
}
