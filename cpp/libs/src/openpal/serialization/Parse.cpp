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
#include "openpal/serialization/Parse.h"

#include "openpal/serialization/Serialization.h"

namespace openpal
{
template <class Serializer>
bool ParseType(RSlice& input, typename Serializer::type_t& output)
{
	if (input.length() < Serializer::size)
	{
		return false;
	}
	else
	{
		output = Serializer::read_from_slice(input);
		return true;
	}
}

bool Parse::read(RSlice &input, uint8_t &output)
{
	return ParseType<UInt8>(input, output);
}

bool Parse::read(RSlice &input, uint16_t &output)
{
	return ParseType<UInt16>(input, output);
}

bool Parse::read(RSlice &input, uint32_t &output)
{
	return ParseType<UInt32>(input, output);
}

bool Parse::read(RSlice &input, UInt48Type &output)
{
	return ParseType<UInt48>(input, output);
}

bool Parse::read(RSlice &input, int16_t &output)
{
	return ParseType<Int16>(input, output);
}

bool Parse::read(RSlice &input, int32_t &output)
{
	return ParseType<Int32>(input, output);
}

bool Parse::read(RSlice &input, double &output)
{
	return ParseType<DoubleFloat>(input, output);
}

bool Parse::read(RSlice &input, float &output)
{
	return ParseType<SingleFloat>(input, output);
}
}


