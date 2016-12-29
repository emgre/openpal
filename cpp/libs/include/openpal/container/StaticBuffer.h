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
#ifndef OPENPAL_STATICBUFFER_H
#define OPENPAL_STATICBUFFER_H

#include "openpal/container/WSlice.h"
#include "openpal/container/RSeq.h"
#include "openpal/util/Comparisons.h"
#include "openpal/util/Uncopyable.h"

#include <limits>

#include <cstdint>

namespace openpal
{

    template <class T, T SIZE>
    class StaticBuffer final
    {
		static_assert(!std::numeric_limits<T>::is_signed && std::numeric_limits<T>::is_integer, "must be an unsigned integer");

    public:  

		StaticBuffer() {}

        RSeq<uint8_t, T> as_seq() const
        {
            return RSeq<uint8_t, T>(buffer_, SIZE);
        }

		RSeq<uint8_t, T> as_seq(T max_size) const
        {
			return this->as_seq().take(max_size);
        }

        WSlice as_wslice()
        {
            return WSlice(buffer_, SIZE);
        }

        WSlice GetWSlice(uint32_t max_size)
        {
            return WSlice(buffer_, openpal::min(SIZE, max_size));
        }

        const uint8_t* operator()() const
        {
            return buffer_;
        }

        uint8_t* operator()()
        {
            return buffer_;
        }

        T size() const
        {
            return SIZE;
        }

    private:

		uint8_t buffer_[SIZE] = { 0 };
    };

}

#endif
