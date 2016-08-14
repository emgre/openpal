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


