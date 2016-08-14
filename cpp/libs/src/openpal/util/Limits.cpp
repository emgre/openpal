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
#include "openpal/util/Limits.h"

#include <float.h>
#include <cstdint>

/// these are implemented in terms of cstdint
/// since AVR doesn't have std::limits
namespace openpal
{

template <>
uint8_t min_value<uint8_t>()
{
	return 0;
}

template <>
uint8_t max_value<uint8_t>()
{
	return UINT8_MAX;
}

template <>
uint16_t min_value<uint16_t>()
{
	return 0;
}

template <>
uint16_t max_value<uint16_t>()
{
	return UINT16_MAX;
}

template <>
float min_value<float>()
{
	return -FLT_MAX;
}

template <>
float max_value<float>()
{
	return FLT_MAX ;
}

template <>
double min_value<double>()
{
	return -DBL_MAX;
}

template <>
double max_value<double>()
{
	return DBL_MAX;
}

template <>
int16_t min_value<int16_t>()
{
	return INT16_MIN;
}

template <>
int16_t max_value<int16_t>()
{
	return INT16_MAX;
}

template <>
int32_t min_value<int32_t>()
{
	return INT32_MIN;
}

template <>
int32_t max_value<int32_t>()
{
	return INT32_MAX;
}

template <>
uint32_t min_value<uint32_t>()
{
	return 0;
}

template <>
uint32_t max_value<uint32_t>()
{
	return UINT32_MAX;
}

template <>
int64_t min_value<int64_t>()
{
	return INT64_MIN;
}

template <>
int64_t max_value<int64_t>()
{
	return INT64_MAX;
}

}
