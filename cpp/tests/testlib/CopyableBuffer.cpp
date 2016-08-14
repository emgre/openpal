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
#include "CopyableBuffer.h"

#include "HexConversions.h"

#include <memory.h>

#include <openpal/util/ToHex.h>
#include <openpal/container/WSlice.h>

using namespace openpal;

namespace openpal
{

std::ostream& operator<<(std::ostream& output, const CopyableBuffer& arBuff)
{
	output << "[" << to_hex(arBuff.as_rslice(), true) << "]";
	return output;
}

CopyableBuffer::CopyableBuffer() :
	buffer_(nullptr),
	length_(0)
{

}

CopyableBuffer::CopyableBuffer(uint32_t size) :
	buffer_(new uint8_t[size]),
	length_(size)
{
	this->zero();
}

CopyableBuffer::CopyableBuffer(const openpal::RSlice& buffer) :
	buffer_(new uint8_t[buffer.length()]),
	length_(buffer.length())
{
	openpal::WSlice dest(buffer_, length_);
    buffer.copy_to(dest);
}

CopyableBuffer::CopyableBuffer(const uint8_t* buff, uint32_t length) :
	buffer_(new uint8_t[length]),
	length_(length)
{
	memcpy(buffer_, buff, length);
}

CopyableBuffer::CopyableBuffer(const CopyableBuffer& arBuffer) :
	buffer_(new uint8_t[arBuffer.Size()]),
	length_(arBuffer.Size())
{
	memcpy(buffer_, arBuffer, length_);
}

void CopyableBuffer::zero()
{
	memset(buffer_, 0, length_);
}

CopyableBuffer& CopyableBuffer::operator=(const CopyableBuffer& arRHS)
{
	//check for assignment to self
	if(this == &arRHS) return *this;

	if(arRHS.Size() != length_)
	{
		length_ = arRHS.Size();
		delete buffer_;
		buffer_ = new uint8_t[length_];
	}

	memcpy(buffer_, arRHS, length_);

	return *this;
}

CopyableBuffer::~CopyableBuffer()
{
	delete [] buffer_;
}

bool CopyableBuffer::operator==( const CopyableBuffer& other) const
{
	if(other.Size() != this->Size()) return false;
	else
	{
		for(size_t i = 0; i < this->Size(); ++i)
		{
			if(this->buffer_[i] != other.buffer_[i]) return false;
		}

		return true;
	}
}

}
