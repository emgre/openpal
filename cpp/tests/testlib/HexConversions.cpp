/*
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
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

