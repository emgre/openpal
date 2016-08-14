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
#include "openpal/serialization/Format.h"

#include "openpal/serialization/Serialization.h"

namespace openpal
{

template <class Serializer>
bool write_type(WSlice &dest, const typename Serializer::type_t& value)
{
	if (dest.length() < Serializer::size)
	{
		return false;
	}
	else
	{
		Serializer::write_to_slice(dest, value);
		return true;
	}
}

bool Format::write(WSlice &dest, const uint8_t &value)
{
	return write_type<UInt8>(dest, value);
}

bool Format::write(WSlice &dest, const uint16_t &value)
{
	return write_type<UInt16>(dest, value);
}

bool Format::write(WSlice &dest, const uint32_t &value)
{
	return write_type<UInt32>(dest, value);
}

bool Format::write(WSlice &dest, const UInt48Type &value)
{
	return write_type<UInt48>(dest, value);
}

bool Format::write(WSlice &dest, const int16_t &value)
{
	return write_type<Int16>(dest, value);
}

bool Format::write(WSlice &dest, const int32_t &value)
{
	return write_type<Int32>(dest, value);
}

bool Format::write(WSlice &dest, const double &value)
{
	return write_type<DoubleFloat>(dest, value);
}

bool Format::write(WSlice &dest, const float &value)
{
	return write_type<SingleFloat>(dest, value);
}
}


