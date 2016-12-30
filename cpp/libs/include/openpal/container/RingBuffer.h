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
#ifndef OPENPAL_RINGBUFFER_H
#define OPENPAL_RINGBUFFER_H

#include <cstdint>



#include "openpal/util/Comparisons.h"

namespace openpal
{

    /**
    	A byte-oriented ring buffer.
    	Interrupt-safe (w/o disabling interrupts) for a single producer
    	and single consumer, one reading and one writing.

    	N must be a power of 2, and is enforced via static assert.
    */
    template <uint8_t SIZE_POWER_OF_TWO>
    class RingBuffer
    {
        static_assert((SIZE_POWER_OF_TWO > 1)&&  !(SIZE_POWER_OF_TWO & (SIZE_POWER_OF_TWO - 1)), "Should use a power of 2 as template parameter, e.g. 16, 32, 64, 128");

    public:

        RingBuffer() : head_(0), tail_(0) {}

        volatile bool put(uint8_t byteIn)
        {
            if(is_full())
            {
                return false;
            }
            else
            {
                buffer_[(head_++) & (SIZE_POWER_OF_TWO - 1)] = byteIn;
                return true;
            }
        }

        volatile bool get(uint8_t& byteOut)
        {
            if(is_empty())
            {
                return false;
            }
            else
            {
                byteOut = buffer_[(tail_++) & (SIZE_POWER_OF_TWO - 1)];
                return true;
            }
        }

        volatile uint8_t get_many(wseq_t& output)
        {
            uint8_t num = openpal::min<uint32_t>(count(), output.length());
            for(uint8_t i = 0; i < num; ++i)
            {
                output[i] = buffer_[(tail_++) & (SIZE_POWER_OF_TWO - 1)];
            }
            output.advance(num);
            return num;
        }

        volatile uint8_t put_many(rseq_t& input)
        {
            uint8_t num = openpal::min<uint32_t>(SIZE_POWER_OF_TWO - count(), input.length());
            for(uint8_t i = 0; i < num; ++i)
            {
                buffer_[(head_++) & (SIZE_POWER_OF_TWO - 1)] = input[i];
            }
            input.advance(num);
            return num;
        }

        volatile inline bool is_full() const
        {
            return count() == SIZE_POWER_OF_TWO;
        }

        volatile inline bool is_empty() const
        {
            return count() == 0;
        }


    private:

        volatile inline uint8_t count() const
        {
            return head_ - tail_;
        }

        uint8_t buffer_[SIZE_POWER_OF_TWO];

        // these may be changed from another thread or interrupt
        volatile uint8_t head_;
        volatile uint8_t tail_;

        RingBuffer(const RingBuffer&) = delete;
        RingBuffer& operator= (const RingBuffer&) = delete;
    };

}

#endif
