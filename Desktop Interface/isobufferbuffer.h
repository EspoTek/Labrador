#ifndef ISOBUFFERBUFFER_H
#define ISOBUFFERBUFFER_H

//isobufferbuffer is a buffer designed for getting the last n things added in reverse order, in O(1) time.

#include <QDebug>
#include <stdlib.h>

class isoBufferBuffer
{
public:
    isoBufferBuffer(int length);
    void add(char newChar);
    char *get(int length);
private:
    int bufferLength;
    int mid;
    int ptr;
    char *buffer;
};

#endif // ISOBUFFERBUFFER_H
