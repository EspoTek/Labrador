#ifndef ISOBUFFERBUFFER_H
#define ISOBUFFERBUFFER_H

//isobufferbuffer is a buffer designed for getting the last n things added in reverse order, in O(1) time.

#include <QDebug>
#include <stdlib.h>
#include <string>

class isoBufferBuffer
{
public:
    isoBufferBuffer(uint32_t length);
    void add(char newChar);
    void add(std::string newString);
    char *get(uint32_t length);
    uint32_t getNumCharsInBuffer();
private:
    uint32_t bufferLength;
    uint32_t mid;
    uint32_t ptr;
    char *buffer;
    uint32_t numCharsInBuffer = 0;
};

#endif // ISOBUFFERBUFFER_H
