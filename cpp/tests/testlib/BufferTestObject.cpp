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
	HexSequence hs(hex);
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

