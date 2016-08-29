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
#include "MockExecutor.h"

#include <algorithm>

using namespace openpal;

namespace openpal
{

    MockExecutor::MockExecutor() :
        post_is_synchronous_(false),
        current_time_(0)
    {

    }

    MockExecutor::~MockExecutor()
    {
        for(auto pTimer : timers_) delete pTimer;
    }

    openpal::Timestamp MockExecutor::next_timer_expiration()
    {
        auto lt = [](MockTimer * pLHS, MockTimer * pRHS)
        {
            return pLHS->expires_at() < pRHS->expires_at();
        };
        auto min = std::min_element(timers_.begin(), timers_.end(), lt);
        if (min == timers_.end())
        {
            return Timestamp();
        }
        else
        {
            return (*min)->expires_at();
        }
    }

    size_t MockExecutor::check_for_expired_timers()
    {
        size_t count = 0;
        while (find_expired_timer())
        {
            ++count;
        }
        return count;
    }

    bool MockExecutor::find_expired_timer()
    {
        auto expired = [this](MockTimer * pTimer)
        {
            return pTimer->expires_at().milliseconds <= this->current_time_.milliseconds;
        };
        auto iter = std::find_if(timers_.begin(), timers_.end(), expired);
        if (iter == timers_.end())
        {
            return false;
        }
        else
        {
            this->post_queue_.push_back((*iter)->action_);
            delete (*iter);
            timers_.erase(iter);
            return true;
        }
    }

    size_t MockExecutor::advance_time(TimeDuration duration)
    {
        this->add_time(duration);
        return this->check_for_expired_timers();
    }

    // doesn't check timers_
    void MockExecutor::add_time(openpal::TimeDuration duration)
    {
        current_time_ = current_time_.add(duration);
    }

    bool MockExecutor::advance_to_next_timer()
    {
        if (timers_.empty())
        {
            return false;
        }
        else
        {
            auto timestamp = next_timer_expiration();
            if (timestamp > current_time_)
            {
                current_time_ = timestamp;
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    bool MockExecutor::run_one()
    {
        this->check_for_expired_timers();

        if(post_queue_.size() > 0)
        {
            auto runnable = post_queue_.front();
            post_queue_.pop_front();
            runnable();
            return true;
        }
        else
        {
            return false;
        }
    }

    size_t MockExecutor::run_many(size_t aMaximum)
    {
        size_t num = 0;
        while(num < aMaximum && this->run_one()) ++num;
        return num;
    }

    void MockExecutor::post(const openpal::action_t& runnable)
    {
        if (post_is_synchronous_)
        {
            runnable();
        }
        else
        {
            post_queue_.push_back(runnable);
        }
    }

    openpal::Timestamp MockExecutor::get_time()
    {
        return current_time_;
    }

    ITimer* MockExecutor::start(const openpal::TimeDuration& aDelay, const openpal::action_t& runnable)
    {
        auto expiration = current_time_.add(aDelay);
        return start(expiration, runnable);
    }

    ITimer* MockExecutor::start(const openpal::Timestamp& arTime, const openpal::action_t& runnable)
    {
        MockTimer* pTimer = new MockTimer(this, arTime, runnable);
        timers_.push_back(pTimer);
        return pTimer;
    }

    void MockExecutor::cancel(ITimer* timer)
    {
        for (timer_vector_t::iterator i = timers_.begin(); i != timers_.end(); ++i)
        {
            if(*i == timer)
            {
                delete timer;
                timers_.erase(i);
                return;
            }
        }
    }

    MockTimer::MockTimer(MockExecutor* apSource, const openpal::Timestamp& arTime, const openpal::action_t& runnable_) :
        time_(arTime),
        source_(apSource),
        action_(runnable_)
    {

    }

    void MockTimer::cancel()
    {
        source_->cancel(this);
    }

    openpal::Timestamp MockTimer::expires_at()
    {
        return time_;
    }

}


