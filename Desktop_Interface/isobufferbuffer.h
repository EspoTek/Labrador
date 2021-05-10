// Copyright (C) 2017, 2018, 2019, 2020, 2021 Christopher Paul Esposito
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef ISOBUFFERBUFFER_H
#define ISOBUFFERBUFFER_H

#include <cstdint>
#include <string>
#include <memory>

/** @file isobufferbuffer.h
 *  @brief This  module  implements  a  data structure that allows
 *  insertion  of  single  characters  and  a  view  of the last N
 *  inserted characters in constant time.
 *
 *  To  obtain  such  complexity,  a  double  ring buffer is used.
 *  That  is,  two  identical  ring buffers are mantained adjacent
 *  in memory. If we always return a pointer to the beginning of a
 *  range  that ends in the second buffer, we will always return a
 *  valid  address(*),  even  when the requested length is greater
 *  than  the  current position being inserted into in the buffer.
 *
 *  (*) By  valid  address  I  mean  that  both the addresses that
 *  represent  the beginning and end of the requested query result
 *  are within the allocated buffer.
 */
class isoBufferBuffer
{
public:
	isoBufferBuffer(uint32_t length);
	~isoBufferBuffer() = default;

	void insert(char c);
	void insert(char const * s);
	void insert(std::string const & s);
	void insert_hex(uint8_t x);

	char const * query(uint32_t length) const;
	// TODO?: add ability to get a copy of the content
	// (e.g. return std::string or Qstring)

	void clear();

	char const * begin() const;
	char const * end() const;

	uint32_t size() const;
	uint32_t capacity() const;
private:
	std::unique_ptr<char[]> m_data;
	uint32_t m_capacity;
	uint32_t m_size = 0;
	uint32_t m_top = 0;
};

#endif // ISOBUFFERBUFFER_H
