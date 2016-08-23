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
#include <openpal/serialization/FloatByteOrder.h>
#include <openpal/util/Comparisons.h>

#include <memory>

using namespace openpal;
using namespace openpal;

using namespace std;

template <class T>
bool TestReadWriteFloat(T value)
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
		if (!(Parse::read(written, readValue) && float_equal(value, readValue)))
		{
			return false;
		}
	}

	return true;
}

template <class T>
bool TestFloatParsing(std::string hex, typename T::type_t value)
{
	Hex hs(hex);
	const uint32_t TYPE_SIZE = static_cast<uint32_t>(sizeof(typename T::type_t));
	REQUIRE((hs.Size() == TYPE_SIZE));

	Buffer buffer(2 * TYPE_SIZE);

	for (uint32_t i = 0; i < TYPE_SIZE; ++i)
	{
		auto dest = buffer.as_wslice();
		dest.advance(i);
		if (!Format::write(dest, value))
		{
			return false;
		}
		auto written = buffer.as_rslice().skip(i);

		typename T::type_t val = 0;
		if (!(Parse::read(written, val) && openpal::float_equal(val, value)))
		{
			return false;
		}
	}

	return true;
}

#define SUITE(name) "FloatSerializationTestSuite - " name

TEST_CASE(SUITE("Float memory byte order is IEEE 754"))
{
	REQUIRE(openpal::FloatByteOrder::order != FloatByteOrder::Value::unsupported);
}

TEST_CASE(SUITE("DoublePacking"))
{
	REQUIRE(TestFloatParsing<openpal::DoubleFloat>("20 74 85 2F C7 2B A2 C0", -2.3258890344E3));
	REQUIRE(TestFloatParsing<openpal::DoubleFloat>("00 00 00 00 64 89 67 41", 12340000.0));
	REQUIRE(TestFloatParsing<openpal::DoubleFloat>("00 00 00 00 00 00 34 C0", -20.0));
	REQUIRE(TestFloatParsing<openpal::DoubleFloat>("8F 81 9C 95 2D F9 64 BB", -13.879E-23));
	REQUIRE(TestFloatParsing<openpal::DoubleFloat>("00 00 00 00 00 00 59 40", 100.0));
}

TEST_CASE(SUITE("SinglePacking"))
{
	REQUIRE(TestFloatParsing<openpal::SingleFloat>("20 4B 3C 4B", 12340000.0f));
	REQUIRE(TestFloatParsing<openpal::SingleFloat>("6D C9 27 9B", -13.879E-23f));
	REQUIRE(TestFloatParsing<openpal::SingleFloat>("00 00 A0 C1", -20.0));
}


TEST_CASE(SUITE("DoubleFloat"))
{
	REQUIRE(TestReadWriteFloat<double>(0.0));
	REQUIRE(TestReadWriteFloat<double>(-100000));
	REQUIRE(TestReadWriteFloat<double>(-2.3258890344E3));
	REQUIRE(TestReadWriteFloat<double>(1E20));
	REQUIRE(TestReadWriteFloat<double>(100.0));
}

TEST_CASE(SUITE("SingleFloat"))
{
	REQUIRE(TestReadWriteFloat<float>(0.0f));
	REQUIRE(TestReadWriteFloat<float>(-100000.0f));
	REQUIRE(TestReadWriteFloat<float>(-2.3258890344E3f));
	REQUIRE(TestReadWriteFloat<float>(1E20f));
	REQUIRE(TestReadWriteFloat<float>(100.0f));
}

