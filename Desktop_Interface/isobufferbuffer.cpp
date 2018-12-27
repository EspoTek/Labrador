#include "isobufferbuffer.h"

#include <QDebug>

/* isoBufferBuffer is implemented as two consecutive, duplicate,
 * ring buffers. the effect of this is that we are able to hand
 * out pointers to pieces of contiguous memory representing the
 * last N inserted elements (for some N <= capacity()) even
 * when we looped back to the begining of the ring buffer less
 * than N insertions ago
 *
 *     There are some differences with the original implementation
 * functionality-wise.
 *     Where the original implementation allowed queries half as
 * long as the length passed in, and allocated a buffer 1.5 times
 * the length passed in, this version allows queries of length up
 * to the length passed into the constructor and allocates a
 * buffer 2 times the length passed in.
 *     Overall, this means that in contrast to the original
 * implementation which only allowed queries up to a third as
 * long as the allocated buffer, we can now do queries as long as
 * half of the allocated buffer, which is a notable improvement.
 */


// TODO: go through the usages of this class and:
// 1. adapt code to use the new interface and remove the old one
// 2. adjust the size of the requested buffer to accomodate
// the improved memory efficiency of the new algorithm

isoBufferBuffer::isoBufferBuffer (
	uint32_t length
) :
	data_(std::make_unique<char[]>(length*2)),
	capacity_(length)
{}

// Adds a character to the end of the buffer
void isoBufferBuffer::insert ( char c ) {
	// Add character to first half of the buffer
	data_[top_] = c;
	// Then to the second
	data_[top_+capacity_] = c;

	// Loop the buffer index if necessary and update size accordingly
	top_ = (top_ + 1) % capacity_;
	size_ = std::min(size_ + 1, capacity_);
}

void isoBufferBuffer::insert ( char const * s ) {
	while ( *s )
		insert(*s++);
}

void isoBufferBuffer::insert ( std::string const & s ) {
	insert(s.c_str());
}

char const* isoBufferBuffer::query ( uint32_t count ) const {
	if ( count > capacity_ )
		qFatal("isoBufferBuffer::query : you may not request more items than the capacity of the buffer");

	if ( count > size_ )
		qFatal("isoBufferBuffer::query : you may not request more items than inserted");

	// we offset the returned pointer to point into the second half of the buffer
	auto offset = capacity_;
	char const * ptr = data_.get() + top_ - count + offset;
	return ptr;
}

void isoBufferBuffer::clear () {
	top_ = 0;
	size_ = 0;
};

char const * isoBufferBuffer::begin () const {
	return data_.get() + top_ - size_ + capacity_;
}

char const * isoBufferBuffer::end () const {
	return data_.get() + top_ + capacity_;
}

uint32_t isoBufferBuffer::size () const {
	return size_;
}

uint32_t isoBufferBuffer::capacity () const {
	return capacity_;
}


// Legacy Interface Implementation
void isoBufferBuffer::add(std::string const & newString) {
    insert(newString);
}


void isoBufferBuffer::add(char newChar) {
	insert(newChar);
}

void isoBufferBuffer::add( uint8_t newByte ) {
	char newString[5];
	sprintf(newString, "0x%02hhx", newByte);
	insert((char const *)newString);
}

uint32_t isoBufferBuffer::getNumCharsInBuffer() {
    return size();
}

char const * isoBufferBuffer::get(uint32_t length) {
	return query(length);
}
