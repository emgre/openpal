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

Hex::Hex( const std::string& hex) :
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

std::string Hex::remove_spaces(const std::string &hex)
{
	std::string copy(hex);
	remove_spaces_in_place(copy);
	return copy;
}

void Hex::remove_spaces_in_place(std::string &hex)
{
	size_t pos = hex.find_first_of(' ');
	if(pos != string::npos)
	{
		hex.replace(pos, 1, "");
		remove_spaces_in_place(hex);
	}
}

uint32_t Hex::validate(const std::string &sequence)
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


