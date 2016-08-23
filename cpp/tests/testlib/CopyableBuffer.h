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
#ifndef TESTLIB_COPYABLEBUFFER_H
#define TESTLIB_COPYABLEBUFFER_H

#include <stddef.h>
#include <memory>
#include <sstream>

#include <openpal/container/RSlice.h>

namespace openpal
{

/** Implements a dynamic buffer with a safe
	copy constructor. This makes it easier to compose with
	classes without requiring an explicit copy constructor
*/
class CopyableBuffer
{
	friend std::ostream& operator<<(std::ostream& output, const CopyableBuffer& arBuff);


public:
	// Construct null buffer_
	CopyableBuffer();
	// Construct based on starting length_ of buffer_
	CopyableBuffer(uint32_t size);
	CopyableBuffer(const openpal::RSlice&);
	CopyableBuffer(const uint8_t* buff, uint32_t length);
	CopyableBuffer(const CopyableBuffer&);
	CopyableBuffer& operator=(const CopyableBuffer&);
	~CopyableBuffer();

	bool operator==( const CopyableBuffer& other) const;
	bool operator!=( const CopyableBuffer& other) const
	{
		return ! (*this == other);
	}

	openpal::RSlice as_rslice() const
	{
		return openpal::RSlice(buffer_, length_);
	}

	operator const uint8_t* () const
	{
		return buffer_;
	}

	operator uint8_t* ()
	{
		return buffer_;
	}

	uint32_t Size() const
	{
		return length_;
	}

	void zero();

protected:
	uint8_t* buffer_;

private:
	uint32_t length_;
};

}

#endif


