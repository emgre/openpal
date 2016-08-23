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
#include "BufferTestObject.h"

#include <testlib/BufferHelpers.h>

#include <memory>
#include <stdexcept>

#include <testlib/HexConversions.h>

#include <openpal/util/ToHex.h>

using namespace openpal;

namespace openpal
{

BufferTestObject::BufferTestObject() :
	num_writes_(0)
{

}

BufferTestObject::~BufferTestObject()
{

}

void BufferTestObject::clear_buffer()
{
	num_writes_ = 0;
	buffer_.clear();
}

bool BufferTestObject::equals(const openpal::RSlice &slice) const
{
	return equals(slice, slice.length());
}

bool BufferTestObject::equals(const uint8_t *apData, size_t aNumBytes) const
{

	if(aNumBytes != buffer_.size()) return false;
	for(size_t i = 0; i < aNumBytes; i++)
		if(apData[i] != buffer_[i])
		{
			return false;
		}
	return true;
}

bool BufferTestObject::contains(const std::string &str) const
{
	std::string s;
	for(size_t i = 0; i < buffer_.size(); ++i)
	{
		std::string c(1, static_cast<char>(buffer_[i]));
		s.append(c);
	}
	return s.find(str) != std::string::npos;
}

std::string BufferTestObject::as_hex_string(bool spaced) const
{
	CopyableBuffer buffer(static_cast<uint32_t>(buffer_.size()));
	for(size_t i = 0; i < buffer_.size(); ++i) buffer[i] = buffer_[i];
	return to_hex(buffer.as_rslice(), spaced);
}


bool BufferTestObject::equals_hex(const std::string &hex) const
{
	Hex hs(hex);
	return equals(hs, hs.Size());
}

bool BufferTestObject::equals(const std::string &str) const
{
	if(str.size() != buffer_.size()) return false;
	for(size_t i = 0; i < buffer_.size(); i++)
		if(str[i] != buffer_[i])
		{
			return false;
		}
	return true;
}

void BufferTestObject::write_to_buffer(const RSlice &slice)
{
	if((buffer_.size() + slice.length()) > max_size )
	{
		throw std::invalid_argument("Max length_ exceeded");
	}
	else
	{
		++num_writes_;

		for(size_t i = 0; i < slice.length(); ++i)
		{
			buffer_.push_back(slice[i]);
		}
	}
}

} //end namespace

