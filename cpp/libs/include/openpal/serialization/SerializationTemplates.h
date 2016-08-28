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
#ifndef OPENPAL_SERIALIZATIONTEMPLATES_H
#define OPENPAL_SERIALIZATIONTEMPLATES_H

#include <cstdint>
#include <cstring>

#include "openpal/container/RSlice.h"
#include "openpal/container/WSlice.h"

#include "openpal/util/Limits.h"

namespace openpal
{

template <class T, uint8_t B0, uint8_t B1>
class Bit16
{

	static_assert((B0 < 2) && (B1 < 2) && (B0 != B1), "bad config");

public:

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

private:

	static T read(const uint8_t *data)
	{
		return (static_cast<T>(data[B0]) << 0) | (static_cast<T>(data[B1]) << 8);
	}

	static void write(uint8_t *data, T value)
	{
		data[B0] = static_cast<uint8_t>(value & 0xFF);
		data[B1] = static_cast<uint8_t>((value >> 8) & 0xFF);
	}

};

template <class T, uint8_t B0, uint8_t B1>
const T Bit16<T, B0, B1>::max_value = openpal::max_value<T>();

template <class T, uint8_t B0, uint8_t B1>
const T Bit16<T, B0, B1>::min_value = openpal::min_value<T>();

template <class T, uint8_t B0, uint8_t B1, uint8_t B2, uint8_t B3>
class Bit32
{
	static_assert((B0 < 4) && (B1 < 4) && (B2 < 4) && (B3 < 4), "bad config");

public:

	static bool write_to(WSlice& dest, T value)
	{
		if (dest.length() < size) return false;

		write(dest, value);
		dest.advance(size);
		return true;
	}

	inline static bool read_from(RSlice &input, T& out)
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

private:

	static T read(const uint8_t *data)
	{
		return	(static_cast<T>(data[B0]) << 0) |
			(static_cast<T>(data[B1]) << 8) |
			(static_cast<T>(data[B2]) << 16) |
			(static_cast<T>(data[B3]) << 24);
	}

	static void write(uint8_t *data, T value)
	{
		data[B0] = static_cast<uint8_t>(value & 0xFF);
		data[B1] = static_cast<uint8_t>((value >> 8) & 0xFF);
		data[B2] = static_cast<uint8_t>((value >> 16) & 0xFF);
		data[B3] = static_cast<uint8_t>((value >> 24) & 0xFF);
	}
};

template <class T, uint8_t B0, uint8_t B1, uint8_t B2, uint8_t B3>
const T Bit32<T, B0, B1, B2, B3>::max_value = openpal::max_value<T>();

template <class T, uint8_t B0, uint8_t B1, uint8_t B2, uint8_t B3>
const T Bit32<T, B0, B1, B2, B3>::min_value = openpal::min_value<T>();

}

#endif
