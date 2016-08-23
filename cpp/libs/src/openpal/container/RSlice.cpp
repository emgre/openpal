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
#include "openpal/container/RSlice.h"

#include "openpal/util/Comparisons.h"

#include "openpal/container/WSlice.h"

#include <cstring>

namespace openpal
{

RSlice RSlice::empty_slice()
{
	return RSlice();
}

RSlice::RSlice(): HasLength(0), buffer_(nullptr)
{}

RSlice::RSlice(uint8_t const* pBuffer, uint32_t length) :
	HasLength(length),
	buffer_(pBuffer)
{}

RSlice RSlice::copy_to(WSlice &dest) const
{
	if (dest.length() < length_)
	{
		return RSlice::empty_slice();
	}
	else
	{
		WSlice copy(dest);
		memcpy(dest, buffer_, length_);
        dest.advance(length_);
		return copy.as_rslice().take(length_);
	}
}

RSlice RSlice::move_to(WSlice &dest) const
{
	if (dest.length() < length_)
	{
		return RSlice::empty_slice();
	}
	else
	{
		WSlice copy(dest);
		memmove(dest, buffer_, length_);
		dest.advance(length_);
		return copy.as_rslice().take(length_);
	}
}

RSlice RSlice::take(uint32_t count) const
{
	return RSlice(buffer_, openpal::min(length_, count));
}

RSlice RSlice::skip(uint32_t count) const
{
	auto num = openpal::min(length_, count);
	return RSlice(buffer_ + num, length_ - num);
}

void RSlice::make_empty()
{
	buffer_ = nullptr;
	length_ = 0;
}

bool RSlice::equals(const RSlice &rhs) const
{
	if (this->length() == rhs.length())
	{
		return memcmp(buffer_, rhs.buffer_, length()) == 0;
	}
	else
	{
		return false;
	}
}

void RSlice::advance(uint32_t count)
{
	auto num = openpal::min(length_, count);
	buffer_ += num;
	length_ -= num;
}

}
