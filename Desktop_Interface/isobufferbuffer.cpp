#include "isobufferbuffer.h"

isoBufferBuffer::isoBufferBuffer(int length)
{
    bufferLength = length;
    mid = length/2;
    buffer = (char *) malloc((length * 3) / 2);
}

void isoBufferBuffer::add(char newChar){
    buffer[ptr] = newChar;
    if(ptr<mid){
        buffer[ptr+bufferLength] = newChar;
    }
    if (ptr >= bufferLength){
        ptr = 0;
    }
    else ptr++;
}

char *isoBufferBuffer::get(int length){
    if (length>mid) qFatal("isoBuffer::get; length requested is too high.");
    if(ptr<mid) return &buffer[ptr+bufferLength - length];
    else return &buffer[ptr - length];
}
