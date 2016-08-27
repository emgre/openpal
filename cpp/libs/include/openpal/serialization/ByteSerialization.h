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
#ifndef OPENPAL_BYTESERIALIZATION_H
#define OPENPAL_BYTESERIALIZATION_H

#include <cstdint>
#include <cstring>

#include "openpal/container/WSlice.h"
#include "openpal/container/RSlice.h"

namespace openpal
{

class UInt8Simple
{
public:

	inline static uint8_t read(const uint8_t* start)
	{
		return (*start);
	}

	inline static bool read_from(RSlice& input, uint8_t& out)
	{
		if (input.length() < size) return false;

		out = read(input);
        input.advance(size);
		return true;
	}

	static bool write_to(WSlice &dest, uint8_t value)
	{
		if (dest.length() < size) return false;

		write(dest, value);
		dest.advance(size);
		return true;
	}

	inline static void write(uint8_t* start, uint8_t value)
	{
		*(start) = value;
	}

	const static size_t size = 1;
	const static uint8_t max_value;
	const static uint8_t min_value;

	typedef uint8_t type_t;
};

}

#endif
