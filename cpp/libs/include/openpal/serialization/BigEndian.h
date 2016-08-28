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
#ifndef OPENPAL_BIGENDIAN_H
#define OPENPAL_BIGENDIAN_H

#include "ByteSerialization.h"
#include "SerializationTemplates.h"

#include "openpal/util/Uncopyable.h"

namespace openpal
{

typedef Bit16<int16_t, 1, 0>			Int16;
typedef Bit16<uint16_t, 1, 0>			UInt16;
typedef Bit32<int32_t, 3, 2, 1, 0>		Int32;
typedef Bit32<uint32_t, 3, 2, 1, 0>		UInt32;
typedef UInt8Simple						UInt8;

class BigEndian : private StaticOnly
{

public:

	template <class T, typename... Args>
	static bool read(openpal::RSlice& input, T& value, Args& ... args)
	{
		return read_one(input, value) && read(input, args...);
	}

	template <class T, typename... Args>
	static bool write(openpal::WSlice& dest, const T& value, const Args& ... args)
	{
		return write_one(dest, value) && write(dest, args...);
	}

private:

	static inline bool read(openpal::RSlice& input) { return true; }

	static inline bool read_one(openpal::RSlice& input, uint8_t& out) 
	{ 
		return UInt8::read_from(input, out);
	}

	static inline bool read_one(openpal::RSlice& input, uint16_t& out)
	{
		return UInt16::read_from(input, out);
	}

	static inline bool read_one(openpal::RSlice& input, uint32_t& out)
	{
		return UInt32::read_from(input, out);
	}

	static inline bool write(openpal::WSlice& dest) { return true; }

	static inline bool write_one(openpal::WSlice& dest, const uint8_t& value) 
	{ 
		return UInt8::write_to(dest, value);
	}

	static inline bool write_one(openpal::WSlice& dest, const uint16_t& value)
	{
		return UInt16::write_to(dest, value);
	}

	static inline bool write_one(openpal::WSlice& dest, const uint32_t& value)
	{
		return UInt32::write_to(dest, value);
	}
};

}

#endif
