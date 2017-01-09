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
	openpal::Timestamp MockExecutor::next_timer_expiration()
    {
        auto lt = [](const std::unique_ptr<MockTimer>& lhs, const std::unique_ptr<MockTimer>& rhs)
        {
            return lhs->expires_at() < rhs->expires_at();
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
        auto expired = [this](const std::unique_ptr<MockTimer>& timer)
        {
            return timer->expires_at().milliseconds <= this->current_time_.milliseconds;
        };
        auto iter = std::find_if(timers_.begin(), timers_.end(), expired);
        if (iter == timers_.end())
        {
            return false;
        }
        else
        {
            this->post_queue_.push_back((*iter)->action_);
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

    ITimer* MockExecutor::start(const openpal::TimeDuration& delay, const openpal::action_t& runnable)
    {
        return start(current_time_.add(delay), runnable);
    }

    ITimer* MockExecutor::start(const openpal::Timestamp& time, const openpal::action_t& runnable)
    {
        auto timer = std::unique_ptr<MockTimer>(new MockTimer(this, time, runnable));
		const auto ret = timer.get();
        timers_.push_back(std::move(timer));
        return ret;
    }

    void MockExecutor::cancel(ITimer* timer)
    {
		const auto result = std::find_if(this->timers_.begin(), this->timers_.end(), [timer](const std::unique_ptr<MockTimer>& item)
		{
			return item.get() == timer;
		});

		if (result != this->timers_.end())
		{
			++num_timer_cancel_;
			this->timers_.erase(result);
		}
    }

    MockTimer::MockTimer(MockExecutor* source, const openpal::Timestamp& time, const openpal::action_t& runnable) :
        time_(time),
        source_(source),
        action_(runnable)
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


