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
#include "openpal/serialization/Format.h"

#include "openpal/serialization/Serialization.h"

namespace openpal
{

template <class Serializer>
bool write_type(WSlice &dest, const typename Serializer::type_t& value)
{
	if (dest.length() < Serializer::size)
	{
		return false;
	}
	else
	{
		Serializer::write_to_slice(dest, value);
		return true;
	}
}

bool Format::write(WSlice &dest, const uint8_t &value)
{
	return write_type<UInt8>(dest, value);
}

bool Format::write(WSlice &dest, const uint16_t &value)
{
	return write_type<UInt16>(dest, value);
}

bool Format::write(WSlice &dest, const uint32_t &value)
{
	return write_type<UInt32>(dest, value);
}

bool Format::write(WSlice &dest, const UInt48Type &value)
{
	return write_type<UInt48>(dest, value);
}

bool Format::write(WSlice &dest, const int16_t &value)
{
	return write_type<Int16>(dest, value);
}

bool Format::write(WSlice &dest, const int32_t &value)
{
	return write_type<Int32>(dest, value);
}

bool Format::write(WSlice &dest, const double &value)
{
	return write_type<DoubleFloat>(dest, value);
}

bool Format::write(WSlice &dest, const float &value)
{
	return write_type<SingleFloat>(dest, value);
}
}


