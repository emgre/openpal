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
#ifndef TESTLIB_BUFFER_TEST_OBJECT_H
#define TESTLIB_BUFFER_TEST_OBJECT_H

#include <string>
#include <vector>
#include <cstdint>

#include <openpal/container/RSlice.h>

namespace openpal
{

class BufferTestObject
{
	static const size_t max_size = 1024 * 1024;

public:
	BufferTestObject();
	~BufferTestObject();

	bool equals(const openpal::RSlice &slice) const;
	bool equals(const uint8_t*, size_t) const;
	bool equals_hex(const std::string& hex) const;
	bool equals(const std::string& str) const;
	bool contains(const std::string &str) const;

	std::string as_hex_string(bool spaced = true) const;

	bool is_buffer_empty()
	{
		return buffer_.size() == 0;
	}

	void clear_buffer();

	size_t size() const
	{
		return buffer_.size();
	}

	bool size_equals(size_t num) const
	{
		return num == size();
	}
	size_t num_writes() const
	{
		return num_writes_;
	}

protected:

	void write_to_buffer(const openpal::RSlice &slice);

private:
	size_t num_writes_;
	std::vector<uint8_t> buffer_;
};

}

#endif

