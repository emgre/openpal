/*
 * Copyright (c) 2016, Automatak LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 * disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef OPENPAL_SERIALIZATIONTEMPLATESBE_H
#define OPENPAL_SERIALIZATIONTEMPLATESBE_H

#include <cstdint>
#include <cstring>

#include "openpal/container/RSlice.h"
#include "openpal/container/WSlice.h"

#include "openpal/util/Limits.h"

namespace openpal
{

template <class T>
class Bit16BE
{
public:

	static T read(const uint8_t *data)
	{
		return (static_cast<T>(data[0]) << 8) | (static_cast<T>(data[1]) << 0);
	}

	static void write(uint8_t *data, T value)
	{
		data[0] = static_cast<uint8_t>((value >> 8) & 0xFF);
		data[1] = static_cast<uint8_t>(value & 0xFF);
	}

	static bool write_to(WSlice &dest, T value)
	{
		if (dest.length() < size) return false;
		
		write(dest, value);
		dest.advance(size);
		return true;
	}

	inline static bool read_from(RSlice& input, T& out)
	{
		if (input.length() < size) return false;

		out = read(input);
        input.advance(size);
		return true;
	}

	typedef T type_t;

	const static size_t size = sizeof(T);
	const static T max_value;
	const static T min_value;
};

template <class T>
const T Bit16BE<T>::max_value = openpal::max_value<T>();

template <class T>
const T Bit16BE<T>::min_value = openpal::min_value<T>();

template <class T>
class Bit32BE
{
public:

	// Endianness doesn't apply to everything. If you do bitwise or bitshift operations on an int, you don't notice the endianness.
	// The machine arranges the multiple bytes, so the least significant byte is still the least significant byte, and the most
	// significant byte is still the most significant byte

	// This is endian independent of the machine order
	static T read(const uint8_t *data)
	{
		return	(static_cast<T>(data[0]) << 24)	|
		        (static_cast<T>(data[1]) << 16)	|
		        (static_cast<T>(data[2]) << 8) |
		        (static_cast<T>(data[3]) << 0);
	}

	static void write(uint8_t *data, T value)
	{
		data[0] = static_cast<uint8_t>((value >> 24) & 0xFF);
		data[1] = static_cast<uint8_t>((value >> 16) & 0xFF);
		data[2] = static_cast<uint8_t>((value >> 8) & 0xFF);
		data[3] = static_cast<uint8_t>(value & 0xFF);
	}

	static bool write_to(WSlice& dest, T value)
	{
		if (dest.length() < size) return false;

		write(dest, value);
		dest.advance(size);
		return true;
	}

	inline static bool read_from(RSlice& input, T& out)
	{
		if (input.length() < size) return false;

		out = read(input);
        input.advance(size);
		return true;
	}

	typedef T type_t;

	const static size_t size = sizeof(T);
	const static T max_value;
	const static T min_value;
};

template <class T>
const T Bit32BE<T>::max_value = openpal::max_value<T>();

template <class T>
const T Bit32BE<T>::min_value = openpal::min_value<T>();

}

#endif
