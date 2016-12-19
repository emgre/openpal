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
#include "openpal/executor/TimeDuration.h"

#include "openpal/util/Limits.h"

namespace openpal
{

    TimeDuration TimeDuration::min_value()
    {
        return TimeDuration(openpal::min_value<int64_t>());
    }

    TimeDuration TimeDuration::max_value()
    {
        return TimeDuration(openpal::max_value<int64_t>());
    }

    TimeDuration TimeDuration::zero_value()
    {
        return TimeDuration(0);
    }

    TimeDuration TimeDuration::milliseconds(int64_t milliseconds)
    {
        return TimeDuration(milliseconds);
    }

    TimeDuration TimeDuration::seconds(int64_t seconds)
    {
        return TimeDuration(1000 * seconds);
    }

    TimeDuration TimeDuration::minutes(int64_t minutes)
    {
        return TimeDuration(static_cast<int64_t>(1000 * 60) * minutes);
    }

    TimeDuration TimeDuration::hours(int64_t hours)
    {
        return TimeDuration(static_cast<int64_t>(1000 * 60 * 60) * hours);
    }

    TimeDuration TimeDuration::days(int64_t days)
    {
        return TimeDuration(static_cast<int64_t>(1000 * 60 * 60 * 24) * days);
    }    

    TimeDuration::TimeDuration(int64_t milliseconds) : TimeDurationBase(milliseconds)
    {}

    bool operator==(const TimeDuration& lhs, const TimeDuration& rhs)
    {
        return lhs.get_milliseconds() == rhs.get_milliseconds();
    }

}
