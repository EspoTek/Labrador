#include "isobufferbuffer.h"

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
