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
#include "BufferHelpers.h"

#include <openpal/util/ToHex.h>

#include "HexConversions.h"

#include <memory.h>
#include <sstream>
#include <assert.h>
#include <algorithm>
#include <exception>
#include <stdexcept>

using namespace std;
using namespace openpal;

namespace openpal
{

ByteStr::ByteStr(uint32_t length, uint8_t seed) : CopyableBuffer(length)
{
	for(size_t i = 0; i < length; ++i) buffer_[i] = static_cast<uint8_t>((i + seed) % 256);
}

ByteStr::ByteStr(const uint8_t* data, uint32_t length) : CopyableBuffer(length)
{
	memcpy(buffer_, data, length);
}

ByteStr::ByteStr(const std::string& str) : CopyableBuffer(static_cast<uint32_t>(str.size()))
{
	memcpy(buffer_, str.c_str(), str.size());
}

bool ByteStr::operator==(const ByteStr& rhs) const
{
	if(Size() != rhs.Size()) return false;

	for(size_t i = 0; i < Size(); ++i)
		if(buffer_[i] != rhs[i]) return false;

	return true;
}

std::string ByteStr::to_hex() const
{
	return openpal::to_hex(as_rslice());
}

HexSequence::HexSequence( const std::string& hex) :
	ByteStr(validate(remove_spaces(hex)))
{
	std::string s = remove_spaces(hex);

	size_t size = s.size();
	for(size_t index = 0, pos = 0; pos < size; ++index, pos += 2)
	{
		uint32_t val;
		std::stringstream ss;
		ss << std::hex << s.substr(pos, 2);
		if((ss >> val).fail())
		{
			throw std::invalid_argument(hex);
		}
		buffer_[index] = static_cast<uint8_t>(val);
	}
}

std::string HexSequence::remove_spaces(const std::string &hex)
{
	std::string copy(hex);
	remove_spaces_in_place(copy);
	return copy;
}

void HexSequence::remove_spaces_in_place(std::string &hex)
{
	size_t pos = hex.find_first_of(' ');
	if(pos != string::npos)
	{
		hex.replace(pos, 1, "");
		remove_spaces_in_place(hex);
	}
}

uint32_t HexSequence::validate(const std::string &sequence)
{
	//annoying when you accidentally put an 'O' instead of zero '0'
	if(sequence.find_first_of( "oO") != string::npos)
	{
		throw std::invalid_argument("Sequence contains 'o' or 'O'");
	}

	if(sequence.size() % 2 != 0)
	{
		throw std::invalid_argument(sequence);
	}

	return static_cast<uint32_t>(sequence.size() / 2);
}

}


