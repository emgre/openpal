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


    bool SingleFloat::read_from(rseq_t& input, float& out)
    {
        if (input.length() < size) return false;

        out = read(input);
        input.advance(size);
        return true;
    }

    bool SingleFloat::write_to(wseq_t& dest, float value)
    {
        if (dest.length() < size) return false;

        write(dest, value);
        dest.advance(size);
        return true;
    }

    float SingleFloat::read(const uint8_t* data)
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

    void SingleFloat::write(uint8_t* dest, float value)
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

