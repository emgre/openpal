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
#include "openpal/executor/TimerRef.h"

namespace openpal
{

TimerRef::TimerRef(openpal::IExecutor& executor) : executor_(&executor), timer_(nullptr)
{}

TimerRef::~TimerRef()
{
	this->cancel();
}


bool TimerRef::is_active() const
{
	return (timer_ != nullptr);
}

Timestamp TimerRef::expires_at() const
{
	return timer_ ? timer_->expires_at() : Timestamp::max_value();
}

bool TimerRef::cancel()
{
	if (timer_)
	{
		timer_->cancel();
		timer_ = nullptr;
		return true;
	}
	else
	{
		return false;
	}
}

bool TimerRef::start(const TimeDuration &timeout, const action_t &action)
{
	if (timer_)
	{
		return false;
	}
	else
	{
		timer_ = executor_->start(timeout, action);
		return true;
	}
}

bool TimerRef::start(const Timestamp &expiration, const action_t &action)
{
	if (timer_)
	{
		return false;
	}
	else
	{
		timer_ = executor_->start(expiration, action);
		return true;
	}
}

void TimerRef::restart(const TimeDuration &timeout, const action_t &action)
{
	if (timer_)
	{
		timer_->cancel();
	}

	timer_ = executor_->start(timeout, action);
}

void TimerRef::restart(const Timestamp &expiration, const action_t &action)
{
	if (timer_)
	{
		timer_->cancel();
	}

	timer_ = executor_->start(expiration, action);
}

}


