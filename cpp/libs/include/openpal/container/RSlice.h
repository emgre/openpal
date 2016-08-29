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
#ifndef OPENPAL_RSLICE_H
#define OPENPAL_RSLICE_H

#include "HasLength.h"

#include <cstdint>

namespace openpal
{

    class WSlice;

    /**
    *	Represents a readonly slice of a buffer located elsewhere. Mediates reading from the buffer
    *	to prevent overreads and other errors.
    */
    class RSlice : public HasLength<uint32_t>
    {

    public:

        static RSlice empty_slice();

        RSlice();

        RSlice(uint8_t const* buffer, uint32_t length);

        void make_empty();

        RSlice copy_to(WSlice& dest) const;

        RSlice move_to(WSlice& dest) const;

        RSlice take(uint32_t count) const;

        RSlice skip(uint32_t count) const;

        bool equals(const RSlice& rhs) const;

        void advance(uint32_t count);

        operator uint8_t const* () const
        {
            return buffer_;
        };

    private:
        uint8_t const* buffer_;

    };

}

#endif
