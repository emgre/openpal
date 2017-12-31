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

namespace openpal
{
	timestamp_t MockExecutor::next_timer_expiration_abs() const
    {
        auto lt = [](const std::shared_ptr<MockTimer>& lhs, const std::shared_ptr<MockTimer>& rhs)
        {
            return lhs->expires_at() < rhs->expires_at();
        };
        auto min = std::min_element(this->timers.begin(), this->timers.end(), lt);
        if (min == this->timers.end())
        {
            return timestamp_t();
        }
        else
        {
            return (*min)->expires_at();
        }
    }

	timestamp_t MockExecutor::next_timer_expiration_rel() const
	{
		auto lt = [](const std::shared_ptr<MockTimer>& lhs, const std::shared_ptr<MockTimer>& rhs)
		{
			return lhs->expires_at() < rhs->expires_at();
		};
		auto min = std::min_element(this->timers.begin(), this->timers.end(), lt);
		if (min == this->timers.end())
		{
			return timestamp_t::max();
		}
		else
		{					
			return timestamp_t((*min)->expires_at() - this->current_time);			
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
        auto expired = [this](const std::shared_ptr<MockTimer>& timer)
        {
            return timer->expires_at() <= this->current_time;
        };

        auto iter = std::find_if(this->timers.begin(), this->timers.end(), expired);
        
		if (iter == this->timers.end())
        {
            return false;
        }
        else
        {
			// keep the timer alive until it's callback is completed.
			auto action = [timer = (*iter), action = (*iter)->action_]() -> void { action(); };
            this->post_queue.push_back(action);
			this->timers.erase(iter);
            return true;
        }
    }

    size_t MockExecutor::advance_time(duration_t duration)
    {
        this->add_time(duration);
        return this->check_for_expired_timers();
    }

    // doesn't check timers_
    void MockExecutor::add_time(duration_t duration)
    {
		this->current_time += duration;
    }

    bool MockExecutor::advance_to_next_timer()
    {
        if (this->timers.empty())
        {
            return false;
        }
        else
        {
            const  auto timestamp = next_timer_expiration_abs();

            if (timestamp > this->current_time)
            {
                this->current_time = timestamp;
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

        if(this->post_queue.size() > 0)
        {
            auto runnable = post_queue.front();
            this->post_queue.pop_front();
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
            this->post_queue.push_back(runnable);
        }
    }

	timestamp_t MockExecutor::get_time()
    {
        return current_time;
    }

    ITimer* MockExecutor::start(const duration_t& delay, const openpal::action_t& runnable)
    {
        return start(current_time + delay, runnable);
    }

    ITimer* MockExecutor::start(const timestamp_t& time, const openpal::action_t& runnable)
    {
        auto timer = std::make_shared<MockTimer>(this, time, runnable);
		const auto ret = timer.get();
        this->timers.push_back(std::move(timer));
        return ret;
    }

    void MockExecutor::cancel(ITimer* timer)
    {
		const auto result = std::find_if(this->timers.begin(), this->timers.end(), [timer](const std::shared_ptr<MockTimer>& item)
		{
			return item.get() == timer;
		});

		if (result != this->timers.end())
		{
			++num_timer_cancel_;
			this->timers.erase(result);
		}
    }

    MockTimer::MockTimer(MockExecutor* source, const timestamp_t& time, const openpal::action_t& runnable) :
        time_(time),
        source_(source),
        action_(runnable)
    {

    }

    void MockTimer::cancel()
    {
        source_->cancel(this);
    }

	timestamp_t MockTimer::expires_at()
    {
        return this->time_;
    }

}


