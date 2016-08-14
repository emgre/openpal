/*
 * Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
 * more contributor license agreements. See the NOTICE file distributed
 * with this work for additional information regarding copyright ownership.
 * Green Energy Corp licenses this file to you under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except in
 * compliance with the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This project was forked on 01/01/2013 by Automatak, LLC and modifications
 * may have been made to this file. Automatak, LLC licenses these modifications
 * to you under the terms of the License.
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

openpal::MonotonicTimestamp MockExecutor::next_timer_expiration()
{
	auto lt = [](MockTimer * pLHS, MockTimer * pRHS)
	{
		return pLHS->expires_at() < pRHS->expires_at();
	};
	auto min = std::min_element(timers_.begin(), timers_.end(), lt);
	if (min == timers_.end())
	{
		return MonotonicTimestamp::max_value();
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

void MockExecutor::post(const openpal::action_t &runnable)
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

openpal::MonotonicTimestamp MockExecutor::get_time()
{
	return current_time_;
}

ITimer* MockExecutor::start(const openpal::TimeDuration &aDelay, const openpal::action_t &runnable)
{
	auto expiration = current_time_.add(aDelay);
	return start(expiration, runnable);
}

ITimer* MockExecutor::start(const openpal::MonotonicTimestamp &arTime, const openpal::action_t &runnable)
{
	MockTimer* pTimer = new MockTimer(this, arTime, runnable);
	timers_.push_back(pTimer);
	return pTimer;
}

void MockExecutor::cancel(ITimer *timer)
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

MockTimer::MockTimer(MockExecutor* apSource, const openpal::MonotonicTimestamp& arTime, const openpal::action_t& runnable_) :
	time_(arTime),
	source_(apSource),
	action_(runnable_)
{

}

void MockTimer::cancel()
{
	source_->cancel(this);
}

openpal::MonotonicTimestamp MockTimer::expires_at()
{
	return time_;
}

}


