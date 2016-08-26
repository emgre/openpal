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
#include <catch.hpp>

#include <openpal/container/Buffer.h>
#include <openpal/serialization/BigEndian.h>


using namespace openpal;
using namespace std;

template <class T>
bool TestReadWrite(typename T::type_t value, std::initializer_list<uint8_t> expected)
{
	Buffer buffer(T::size);

	T::write(buffer.as_wslice(), value);

	if (expected.size() != T::size) {
		return false;
	}

	auto i = 0;

	for (auto& byte : expected) {
		if (buffer[i] != byte) {
			return false;
		}
		++i;
	}

	return T::read(buffer.as_rslice()) == value;

}


#define SUITE(name) "BigEndianSerializationTestSuite - " name

TEST_CASE(SUITE("UInt8"))
{
	REQUIRE( TestReadWrite<UInt8>(0, {0}) );
	REQUIRE(TestReadWrite<UInt8>(123, {0x7B}));
	REQUIRE(TestReadWrite<UInt8>(255, {0xFF}));
}

TEST_CASE(SUITE("UInt16"))
{
	REQUIRE(TestReadWrite<UInt16>(0, { 0, 0 }));
	REQUIRE(TestReadWrite<UInt16>(123, { 0x00, 0x7B, }));
	REQUIRE(TestReadWrite<UInt16>(UInt16::max_value, { 0xFF, 0xFF }));
}

TEST_CASE(SUITE("Int16"))
{
	REQUIRE(TestReadWrite<Int16>(0, { 0, 0 }));
	REQUIRE(TestReadWrite<Int16>(Int16::min_value, { 0x80, 0x00 }));
	REQUIRE(TestReadWrite<Int16>(Int16::max_value, { 0x7F, 0xFF }));
}

TEST_CASE(SUITE("UInt32"))
{
	REQUIRE(TestReadWrite<UInt32>(0, { 0x00, 0x00, 0x00 , 0x00 }));
	REQUIRE(TestReadWrite<UInt32>(123, { 0x00, 0x00, 0x00 , 0x7B }));
	REQUIRE(TestReadWrite<UInt32>(UInt32::max_value, { 0xFF, 0xFF, 0xFF, 0xFF }));
}

TEST_CASE(SUITE("Int32"))
{
	REQUIRE(TestReadWrite<Int32>(0, { 0x00, 0x00, 0x00 , 0x00 }));
	REQUIRE(TestReadWrite<Int32>(Int32::min_value, { 0x80, 0x00, 0x00, 0x00 }));
	REQUIRE(TestReadWrite<Int32>(Int32::max_value, { 0x7F, 0xFF, 0xFF, 0xFF }));
}
