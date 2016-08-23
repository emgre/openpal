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
