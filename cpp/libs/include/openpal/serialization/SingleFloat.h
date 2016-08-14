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
#ifndef OPENPAL_SINGLE_FLOAT_H
#define OPENPAL_SINGLE_FLOAT_H

#include "openpal/util/Uncopyable.h"
#include "openpal/container/RSlice.h"
#include "openpal/container/WSlice.h"

#include <cstddef>

namespace openpal
{

class SingleFloat : private StaticOnly
{
public:

	static_assert(sizeof(float) == 4, "Unexpected length_ of single float");

	typedef float type_t;

	static float read_from_slice(RSlice& slice);
	static void write_to_slice(WSlice& dest, float value);

	static float read(const uint8_t *data);
	static void write(uint8_t *data, float value);

	const static std::size_t size = sizeof(float);
	const static float max_value;
	const static float min_value;
};

}

#endif
