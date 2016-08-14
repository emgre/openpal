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
#include "openpal/serialization/SingleFloat.h"

#include "openpal/util/Limits.h"
#include "openpal/serialization/FloatByteOrder.h"

#include <cstring>

namespace openpal
{
const float SingleFloat::max_value(openpal::max_value<float>());
const float SingleFloat::min_value(openpal::min_value<float>());

union SingleFloatUnion
{
	uint8_t bytes[4];
	float value;
};


float SingleFloat::read_from_slice(RSlice &slice)
{
	auto ret = read(slice);
    slice.advance(size);
	return ret;
}

void SingleFloat::write_to_slice(WSlice &dest, float value)
{
	write(dest, value);
	dest.advance(size);
}

float SingleFloat::read(const uint8_t *data)
{
	if (FloatByteOrder::order == FloatByteOrder::Value::normal)
	{
		SingleFloatUnion x = {{ data[0], data[1], data[2], data[3] }};
		return x.value;
	}
	else
	{
		SingleFloatUnion x = {{ data[3], data[2], data[1], data[0] }};
		return x.value;
	}
}

void SingleFloat::write(uint8_t *dest, float value)
{
	if (FloatByteOrder::order == FloatByteOrder::Value::normal)
	{
		memcpy(dest, &value, size);
	}
	else
	{
		auto data = reinterpret_cast<uint8_t*>(&value);
		uint8_t bytes[4] = { data[3], data[2], data[1], data[0] };
		memcpy(dest, bytes, size);
	}
}
}

