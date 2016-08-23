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
#include "HexConversions.h"

#include "BufferHelpers.h"

#include <openpal/util/ToHex.h>
#include <openpal/container/Buffer.h>

#include <sstream>

using namespace std;
using namespace openpal;

namespace openpal
{

std::string to_hex(const uint8_t *buffer, size_t aLength, bool spaced)
{
	std::ostringstream oss;
	size_t last = aLength - 1;
	for (size_t i = 0; i < aLength; i++)
	{
		char c = buffer[i];
		oss << openpal::to_hex_char((c & 0xf0) >> 4) << openpal::to_hex_char(c & 0xf);
		if (spaced && i != last)oss << " ";
	}
	return oss.str();
}

std::string to_hex(const RSlice &buffer, bool spaced)
{
	return to_hex(buffer, buffer.length(), spaced);
}

std::string byte_to_hex(uint8_t b)
{
	std::ostringstream oss;
	oss << openpal::to_hex_char((b & 0xf0) >> 4) << openpal::to_hex_char(b & 0xf);
	return oss.str();
}

std::string append_hex(std::initializer_list<std::string> segments)
{
	ostringstream oss;
	for (auto & str : segments)
	{
		oss << str;
	}
	Hex output(oss.str());
	return to_hex(output.as_rslice());
}

std::string skip_bytes_hex(const std::string &input, uint32_t bytes)
{
	Hex buffer(input);
	return to_hex(buffer.as_rslice().skip(bytes));
}

std::string repeat_hex(uint8_t byte, uint16_t count, bool spaced)
{
	Buffer buffer(count);
	buffer.as_wslice().set_all_to(byte);
	return to_hex(buffer.as_rslice(), spaced);
}

std::string increment_hex(uint8_t start, uint16_t count, bool spaced)
{
	Buffer buffer(count);

	for (uint16_t i = 0; i < count; ++i)
	{
		buffer[i] = start;
		++start;
	}

	return to_hex(buffer.as_rslice(), spaced);
}

}

