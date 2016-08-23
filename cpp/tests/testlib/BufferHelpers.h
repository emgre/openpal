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
#ifndef TESTLIB_BUFFERHELPERS_H
#define TESTLIB_BUFFERHELPERS_H

#include "CopyableBuffer.h"

#include <string>

namespace openpal
{

class ByteStr : public CopyableBuffer
{

public:
	ByteStr(uint32_t length, uint8_t seed = 0);
	ByteStr(const uint8_t* data, uint32_t length);
	ByteStr(const std::string& str);
	bool operator==(const ByteStr& rhs) const;
	std::string to_hex() const;
};

/**
 * A sequence of hex values in the form "01 02 03 04" that are stored as a ByteStr.
 */
class Hex : public ByteStr
{
public:
	Hex(const std::string& hex);

	operator openpal::RSlice () const
	{
		return this->as_rslice();
	}

private:
	std::string remove_spaces(const std::string& hex);
	void remove_spaces_in_place(std::string& hex);
	static uint32_t validate(const std::string& sequence);
};

}

#endif
