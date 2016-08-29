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
#ifndef OPENPAL_TIMERREF_H
#define OPENPAL_TIMERREF_H

#include "openpal/executor/ITimer.h"
#include "openpal/executor/IExecutor.h"
#include "openpal/util/Uncopyable.h"

namespace openpal
{

    /**
    * A management class to make dealing with timer pointers safer a little safer
    *
    * Holds an optional pointer to an active ITimer pointer. Acts as a safe proxy for dealing with a recurring timer instance.
    */
    class TimerRef : openpal::Uncopyable
    {

    public:
        TimerRef(openpal::IExecutor& executor);

        // automatically cancels any active timers_ on destructive
        ~TimerRef();

        // Called to see if the timer is currently active
        bool is_active() const;

        // return the expiration time, Timestamp::max_value() if not active
        Timestamp expires_at() const;

        // cancels any existing timer, returning true if the timer was active, false otherwise
        bool cancel();

        // restart the timer, return false if already active
        bool start(const TimeDuration& timeout, const action_t& action);
        bool start(const Timestamp& expiration, const action_t& action);

        // start a new timer, canceling any existing timer
        void restart(const TimeDuration& expiration, const action_t& action);
        void restart(const Timestamp& expiration, const action_t& action);

    private:

        IExecutor* executor_;
        ITimer* timer_;
    };

}

#endif
