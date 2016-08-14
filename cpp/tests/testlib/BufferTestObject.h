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

