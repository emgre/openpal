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
#include "openpal/serialization/FloatByteOrder.h"


namespace openpal
{

    const FloatByteOrder::Value FloatByteOrder::order(get_byte_order());

    union FloatUnion
    {
        uint8_t bytes[4];
        float f;
    };

    static_assert(sizeof(FloatUnion) == 4, "Bad float union length_");

    bool FloatByteOrder::is_normal_byte_order()
    {
        FloatUnion value = {{ 0x00, 0x00, 0xA0, 0xC1 }};
        return (value.f == -20.0f);
    }

    bool FloatByteOrder::is_reverse_byte_order()
    {
        FloatUnion value = {{ 0xC1, 0xA0, 0x00, 0x00 }};
        return (value.f == -20.0f);
    }

    FloatByteOrder::Value FloatByteOrder::get_byte_order()
    {
        if (is_normal_byte_order())
        {
            return FloatByteOrder::Value::normal;
        }
        else if (is_reverse_byte_order())
        {
            return FloatByteOrder::Value::reverse;
        }
        else
        {
            return FloatByteOrder::Value::unsupported;
        }
    }


}


