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

#include <testlib/BufferHelpers.h>
#include <testlib/HexConversions.h>

#include <openpal/container/Buffer.h>
#include <openpal/serialization/Parse.h>
#include <openpal/serialization/Format.h>
#include <openpal/serialization/Serialization.h>
#include <openpal/util/Comparisons.h>

#include <memory>

using namespace openpal;
using namespace openpal;

using namespace std;

template <class T>
bool TestReadWrite(T value)
{
	Buffer buffer(2 * sizeof(T));

	for (uint32_t i = 0; i < sizeof(T); ++i)
	{
		auto dest = buffer.as_wslice();
		dest.advance(i);
		if (!Format::write(dest, value))
		{
			return false;
		}

		auto written = buffer.as_rslice().skip(i);
		T readValue;
		if (!(Parse::read(written, readValue) && value == readValue))
		{
			return false;
		}
	}

	return true;
}


#define SUITE(name) "IntegerSerializationTestSuite - " name

TEST_CASE(SUITE("UInt8"))
{
	REQUIRE(TestReadWrite<uint8_t>(0));
	REQUIRE(TestReadWrite<uint8_t>(123));
	REQUIRE(TestReadWrite<uint8_t>(255));
}

TEST_CASE(SUITE("UInt16"))
{
	REQUIRE(TestReadWrite<uint16_t>(0));
	REQUIRE(TestReadWrite<uint16_t>(123));
	REQUIRE(TestReadWrite<uint16_t>(65535));
}

TEST_CASE(SUITE("UInt16 read from little endian"))
{
	uint8_t arr[2] = { 0x01, 0x02 };

	// 2*256 + 1
	REQUIRE(UInt16::read(arr) == 513);
}

TEST_CASE(SUITE("Int16"))
{
	REQUIRE(TestReadWrite<int16_t>(-32768));
	REQUIRE(TestReadWrite<int16_t>(0));
	REQUIRE(TestReadWrite<int16_t>(32767));
}

TEST_CASE(SUITE("Int16 read from little endian"))
{
	uint8_t arr[2] = { 0x00, 0x80 };

	// 2*256 + 1
	REQUIRE(Int16::read(arr) == openpal::min_value<int16_t>());
}

TEST_CASE(SUITE("UInt32"))
{
	REQUIRE(TestReadWrite<uint32_t>(0));
	REQUIRE(TestReadWrite<uint32_t>(123));
	REQUIRE(TestReadWrite<uint32_t>(4294967295UL));
}

TEST_CASE(SUITE("UInt32 read from little endian"))
{
	uint8_t arr[4] = { 0x01, 0x02, 0x00, 0x00 };

	// 2*256 + 1
	REQUIRE(UInt32::read(arr) == 513);
}

TEST_CASE(SUITE("Int32"))
{
	REQUIRE(TestReadWrite<int32_t>(0x80000000));
	REQUIRE(TestReadWrite<int32_t>(0));
	REQUIRE(TestReadWrite<int32_t>(0x7fffffff));
}

TEST_CASE(SUITE("Int32 read from little endian"))
{
	uint8_t arr[4] = { 0x00, 0x00, 0x00, 0x80 };

	REQUIRE(Int32::read(arr) == openpal::min_value<int32_t>());
}

TEST_CASE(SUITE("UInt48"))
{
	REQUIRE(TestReadWrite<UInt48Type>(UInt48Type(0)));
	REQUIRE(TestReadWrite<UInt48Type>(UInt48Type(123)));
	REQUIRE(TestReadWrite<UInt48Type>(UInt48Type(281474976710655ULL)));
}

TEST_CASE(SUITE("UInt48  read from little endian"))
{
	uint8_t arr[6] = { 0x01, 0x02, 0x00, 0x00, 0x00, 0x00};

	// 2*256 + 1
	REQUIRE(UInt48::read(arr) == 513);
}


TEST_CASE(SUITE("ParseMany"))
{
	Hex hex("FF AB BA 01 00 00 00 CC");

	uint8_t first = 0;
	uint16_t second = 0;
	uint32_t third = 0;

	{
		auto input = hex.as_rslice();
		REQUIRE(Parse::many(input, first, second, third));
		REQUIRE(first == 255);
		REQUIRE(second == 0xBAAB);
		REQUIRE(third == 1);
		REQUIRE(input.length() == 1); // 1 byte remaining
	}

	{
		auto input = hex.as_rslice().skip(2);
		REQUIRE_FALSE(Parse::many(input, first, second, third));
	}
}


TEST_CASE(SUITE("FormatMany"))
{

	uint8_t first = 255;
	uint16_t second = 0xBAAB;
	uint32_t third = 1;

	const uint32_t SIZE = 7;

	Buffer output(SIZE + 3);

	{
		auto dest = output.as_wslice();
		REQUIRE(Format::many(dest, first, second, third));
		REQUIRE(dest.length() == (output.length() - SIZE));
		auto written = to_hex(output.as_rslice().take(SIZE));
		REQUIRE(written == "FF AB BA 01 00 00 00");
	}

	{
		auto dest = output.as_wslice(SIZE - 1);
		REQUIRE_FALSE(Format::many(dest, first, second, third));
	}
}