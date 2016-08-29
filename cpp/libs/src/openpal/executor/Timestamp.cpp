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
#include "openpal/executor/Timestamp.h"

#include <stdint.h>

namespace openpal
{

    Timestamp Timestamp::max_value()
    {
        return Timestamp(INT64_MAX);
    }

    Timestamp Timestamp::min_value()
    {
        return Timestamp(INT64_MIN);
    }

    bool Timestamp::is_max_value() const
    {
        return milliseconds == INT64_MAX;
    }

    bool Timestamp::is_min_value() const
    {
        return milliseconds == INT64_MIN;
    }

    Timestamp::Timestamp() : milliseconds(0)
    {}

    Timestamp::Timestamp(int64_t aMilliseconds) : milliseconds(aMilliseconds)
    {}


    Timestamp Timestamp::add(const TimeDuration& duration) const
    {
        return Timestamp(milliseconds + duration.get_milliseconds());
    }

    bool operator==(const Timestamp& first, const Timestamp& second)
    {
        return first.milliseconds == second.milliseconds;
    }

    bool operator<(const Timestamp& first, const Timestamp& second)
    {
        return first.milliseconds < second.milliseconds;
    }

    bool operator>(const Timestamp& first, const Timestamp& second)
    {
        return first.milliseconds > second.milliseconds;
    }

}

