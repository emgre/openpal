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
#include "openpal/container/WSlice.h"

#include "openpal/util/Comparisons.h"
#include "openpal/container/RSlice.h"

#include <cstring>

namespace openpal
{

WSlice WSlice::empty_slice()
{
	return WSlice();
}

WSlice::WSlice():
	HasLength(0),
	buffer_(nullptr)
{}

void WSlice::set_all_to(uint8_t value)
{
	memset(buffer_, value, length_);
}

WSlice::WSlice(uint8_t* buffer, uint32_t length) :
	HasLength(length),
	buffer_(buffer)
{}

void WSlice::make_empty()
{
	buffer_ = nullptr;
	length_ = 0;
}

uint32_t WSlice::advance(uint32_t count)
{
	auto num = openpal::Min(count, length_);
	buffer_ += num;
	length_ -= num;
	return num;
}

WSlice WSlice::skip(uint32_t count) const
{
	auto num = openpal::Min(count, length_);
	return WSlice(buffer_ + num, length_ - num);
}

RSlice WSlice::as_rslice() const
{
	return RSlice(buffer_, length_);
}

}


