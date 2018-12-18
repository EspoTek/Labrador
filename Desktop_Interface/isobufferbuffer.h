#ifndef ISOBUFFERBUFFER_H
#define ISOBUFFERBUFFER_H

//isobufferbuffer is a buffer designed for getting the last n things added in reverse order, in O(1) time.

#include <QDebug>
#include <stdlib.h>
#include <string>
#include <memory>

class isoBufferBuffer
{
public:
    isoBufferBuffer ( uint32_t length );
	~isoBufferBuffer () = default;

	void insert ( char );
	char const * query ( uint32_t length ) const;

	uint32_t size () const;
	uint32_t capacity () const;
	
	// Legacy Interface
	void add(uint8_t newByte);
    void add(char newChar);
    void add(std::string const & newString);
    char const *get(uint32_t length);
    uint32_t getNumCharsInBuffer();
private:
	std::unique_ptr<char[]> data_;
	uint32_t capacity_;
	uint32_t size_ = 0;
	uint32_t top_ = 0;
};

#endif // ISOBUFFERBUFFER_H
