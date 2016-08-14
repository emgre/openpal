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
#include "openpal/container/Buffer.h"

namespace openpal
{
Buffer::Buffer() : Array<uint8_t, uint32_t>(0)
{}

Buffer::Buffer(uint32_t size) : Array<uint8_t, uint32_t>(size)
{}

Buffer::Buffer(const RSlice& input) : Array<uint8_t, uint32_t>(input.length())
{
	auto dest = this->as_wslice();
	input.copy_to(dest);
}

RSlice Buffer::as_rslice() const
{
	return RSlice(this->buffer_, this->length_);
}

WSlice Buffer::as_wslice()
{
	return WSlice(this->buffer_, this->length());
}

WSlice Buffer::as_wslice(uint32_t max_size)
{
	if (max_size <= this->length())
	{
		return WSlice(this->buffer_, max_size);
	}
	else
	{
		return as_wslice();
	}
}
}

