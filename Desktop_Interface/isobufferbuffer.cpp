#include "isobufferbuffer.h"

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

// TODO: go through the usages of this class and adjust the
// size of the requested buffer to accomodate the improved memory
// efficiency of the new algorithm

isoBufferBuffer::isoBufferBuffer(
	uint32_t length
) :
	data_ ( std::make_unique<char[]>(length*2) ),
	capacity_ (length)
{}

void isoBufferBuffer::insert (
	char c
) {
	data_[top_] = c;
	data_[top_+capacity_] = c;

	top_ = (top_+1) % capacity_;
	size_ = std::min(size_+1, capacity_);
}

char const * isoBufferBuffer::query (
	uint32_t length
) const {
	uint32_t offset = top_ < length ? capacity_ : 0 ;
	return data_.get() + top_ - length + offset;
}

uint32_t isoBufferBuffer::size () const {
	return size_;
}

uint32_t isoBufferBuffer::capacity () const {
	return capacity_;
}


// Legacy Interface Implementation
void isoBufferBuffer::add(std::string const & newString)
{
    for (char newChar : newString)
        insert(newChar);
}


void isoBufferBuffer::add(char newChar){
	insert(newChar);
}

void isoBufferBuffer::add(uint8_t newByte)
{
	char newString[3];
	sprintf(newString, "%02hhx", newByte);
	
	insert('0');
	insert('x');
	insert(newString[0]);
	insert(newString[1]);
}

uint32_t isoBufferBuffer::getNumCharsInBuffer()
{
    return size();
}

char const * isoBufferBuffer::get(uint32_t length){
    if (length > size_)
        qFatal("isoBuffer::get; length requested is too high.");
	return query(length);
}
