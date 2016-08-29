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
        auto num = openpal::min(count, length_);
        buffer_ += num;
        length_ -= num;
        return num;
    }

    WSlice WSlice::skip(uint32_t count) const
    {
        auto num = openpal::min(count, length_);
        return WSlice(buffer_ + num, length_ - num);
    }

    RSlice WSlice::as_rslice() const
    {
        return RSlice(buffer_, length_);
    }

}


