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
#ifndef OPENPAL_STATICBUFFER_H
#define OPENPAL_STATICBUFFER_H

#include "openpal/container/WSlice.h"
#include "openpal/container/RSlice.h"
#include "openpal/util/Comparisons.h"
#include "openpal/util/Uncopyable.h"

#include <cstdint>

namespace openpal
{

template <uint32_t SIZE>
class StaticBuffer final
{

public:

	StaticBuffer()
	{}

	RSlice as_rslice() const
	{
		return RSlice(buffer_, SIZE);
	}

	RSlice as_rslice(uint32_t max_size) const
	{
		return RSlice(buffer_, openpal::min(SIZE, max_size));
	}

	WSlice as_wslice()
	{
		return WSlice(buffer_, SIZE);
	}

	WSlice GetWSlice(uint32_t max_size)
	{
		return WSlice(buffer_, openpal::min(SIZE, max_size));
	}

	const uint8_t* operator()() const
	{
		return buffer_;
	}

	uint8_t* operator()()
	{
		return buffer_;
	}

	uint32_t size() const
	{
		return SIZE;
	}

private:
	uint8_t buffer_[SIZE];
};

}

#endif
