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
#ifndef OPENPAL_TIMEDURATION_H
#define OPENPAL_TIMEDURATION_H

#include <cstdint>

namespace openpal
{

    template <class T>
    class TimeDurationBase
    {

    public:

        T get_milliseconds() const
        {
            return milliseconds_;
        }

        bool is_negative() const
        {
            return milliseconds_ < 0;
        }

        bool is_postive() const
        {
            return milliseconds_ > 0;
        }

        operator T() const
        {
            return milliseconds_;
        }

    protected:

        TimeDurationBase() : milliseconds_(0)
        {}

        TimeDurationBase(T milliseconds) : milliseconds_(milliseconds)
        {}

        T milliseconds_;
    };


    /**
    *  Strong typing for millisecond based time durations
    */
    class TimeDuration : public TimeDurationBase<int64_t>
    {

    public:

        TimeDuration();

        static TimeDuration min_value();

        static TimeDuration max_value();

        static TimeDuration zero_value();

        static TimeDuration milliseconds(int64_t milliseconds);

        static TimeDuration seconds(int64_t seconds);

        static TimeDuration minutes(int64_t minutes);

        static TimeDuration hours(int64_t hours);

        static TimeDuration days(int64_t days);

    private:

        TimeDuration(int64_t milliseconds);
    };

    bool operator==(const TimeDuration& lhs, const TimeDuration& rhs);

}

#endif
