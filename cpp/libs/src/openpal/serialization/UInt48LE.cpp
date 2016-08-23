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
#include "openpal/serialization/UInt48LE.h"

namespace openpal
{

UInt48Type UInt48LE::read(const uint8_t *data)
{
	return UInt48Type(
	           (static_cast<uint64_t>(data[0]) << 0) |
	           (static_cast<uint64_t>(data[1]) << 8) |
	           (static_cast<uint64_t>(data[2]) << 16) |
	           (static_cast<uint64_t>(data[3]) << 24) |
	           (static_cast<uint64_t>(data[4]) << 32) |
	           (static_cast<uint64_t>(data[5]) << 40));
}

void UInt48LE::write(uint8_t *data, UInt48Type value)
{
	if (value > max_value)
	{
		value = UInt48Type(max_value);
	}

	data[0] = static_cast<uint8_t>(value & 0xFF);
	data[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
	data[2] = static_cast<uint8_t>((value >> 16) & 0xFF);
	data[3] = static_cast<uint8_t>((value >> 24) & 0xFF);
	data[4] = static_cast<uint8_t>((value >> 32) & 0xFF);
	data[5] = static_cast<uint8_t>((value >> 40) & 0xFF);
}

}

