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
#include "openpal/serialization/DoubleFloat.h"

#include "openpal/util/Limits.h"
#include "openpal/serialization/FloatByteOrder.h"

#include <cstring>

namespace openpal
{
const double DoubleFloat::max_value(openpal::max_value<double>());
const double DoubleFloat::min_value(openpal::min_value<double>());

union DoubleFloatUnion
{
	uint8_t bytes[8];
	double value;
};

double DoubleFloat::read_from_slice(RSlice &buffer)
{
	auto ret = read(buffer);
    buffer.advance(size);
	return ret;
}

void DoubleFloat::write_to_slice(WSlice &buffer, double value)
{
	write(buffer, value);
	buffer.advance(size);
}

double DoubleFloat::read(const uint8_t *data)
{
	if (FloatByteOrder::order == FloatByteOrder::Value::normal)
	{
		DoubleFloatUnion x = {{ data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7] }};
		return x.value;
	}
	else
	{
		DoubleFloatUnion x = {{ data[7], data[6], data[5], data[4], data[3], data[2], data[1], data[0] }};
		return x.value;
	}
}

void DoubleFloat::write(uint8_t *dest, double value)
{
	if (FloatByteOrder::order == FloatByteOrder::Value::normal)
	{
		memcpy(dest, &value, size);
	}
	else
	{
		auto data = reinterpret_cast<uint8_t*>(&value);
		uint8_t bytes[8] = { data[7], data[6], data[5], data[4], data[3], data[2], data[1], data[0] };
		memcpy(dest, bytes, size);
	}
}
}

