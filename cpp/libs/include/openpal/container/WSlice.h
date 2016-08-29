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
#ifndef OPENPAL_WSLICE_H
#define OPENPAL_WSLICE_H

#include "HasLength.h"

#include <cstdint>

namespace openpal
{

    class RSlice;

    /**
    *	Represents a write-able slice of a buffer located elsewhere. Mediates writing to the buffer
    *	to prevent overruns and other errors.
    */
    class WSlice : public HasLength<uint32_t>
    {
    public:

        static WSlice empty_slice();

        void set_all_to(uint8_t value);

        WSlice();
        WSlice(uint8_t* buffer, uint32_t length);

        void make_empty();

        uint32_t advance(uint32_t count);

        WSlice skip(uint32_t count) const;

		WSlice take(uint32_t count) const;

        RSlice as_rslice() const;

        operator uint8_t* ()
        {
            return buffer_;
        };

        operator uint8_t const* () const
        {
            return buffer_;
        };

    private:

        uint8_t* buffer_;
    };


}

#endif
