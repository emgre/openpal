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
