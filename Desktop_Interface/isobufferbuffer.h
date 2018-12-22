#ifndef ISOBUFFERBUFFER_H
#define ISOBUFFERBUFFER_H

#include <QDebug>
#include <cstdint>
#include <string>
#include <memory>

/** @file isobufferbuffer.h
 *  @brief This module implements a data structure that allows insertion of single characters and a view of the last N inserted characters in constant time
 *
 *  To obtain such complexity, a double ring buffer is used. That is, two identical ring buffers are mantained adjacent in memory.
 *  If we always return a pointer into the second buffer, even when the requested length is greater than the current position in the buffer, we will return a valid address(*).
 *
 *  (*)by valid address it is meant that the address is within the allocated buffer.
 */
class isoBufferBuffer {
public:
	isoBufferBuffer ( uint32_t length );
	~isoBufferBuffer () = default;

	void insert ( char c );
	void insert ( char const * s );
	void insert ( std::string const & s );

	char const * query ( uint32_t length ) const;
	//TODO?: add ability to get a copy of the content (i.e. return std::string or Qstring)

	void clear ();

	char const * begin () const;
	char const * end () const;

	uint32_t size () const;
	uint32_t capacity () const;
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
