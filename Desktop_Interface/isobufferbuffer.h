#ifndef ISOBUFFERBUFFER_H
#define ISOBUFFERBUFFER_H

//isobufferbuffer is a buffer designed for getting the last n things added in reverse order, in O(1) time.

#include <QDebug>
#include <stdlib.h>
#include <string>
#include <memory>

// Data structure that supports the following operations:
// insert: inserts a character at the end - O(1)
// query: returns a pointer to the last N inserted elements - O(1)
// add(char)    - legacy - inserts a character
// add(uint8_t) - legacy - inserts a hex representation of a byte
// add(string)  - legacy - inserts every character in a string
class isoBufferBuffer
{
public:
	// NOTE:
	// While this was re-implemented to conform to more modern
	// standars, a few decisions were made to better fit with
	// the existing style.
	
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
