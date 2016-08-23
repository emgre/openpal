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
#ifndef TESTLIB_MOCK_EXECUTOR_H
#define TESTLIB_MOCK_EXECUTOR_H

#include <openpal/executor/IExecutor.h>

#include <map>
#include <queue>
#include <limits>
#include <stddef.h>

namespace openpal
{

class MockTimer;

/** @section desc Test class that doles out MockTimer* */
class MockExecutor final : public openpal::IExecutor
{
	friend class MockTimer;

public:
	MockExecutor();
	~MockExecutor();

	// Implement IExecutor
	virtual openpal::ITimer* start(const openpal::Timestamp &, const openpal::action_t &action) override;
	virtual openpal::ITimer* start(const openpal::TimeDuration &, const openpal::action_t &action) override;
	virtual void post(const openpal::action_t &action) override;
	virtual openpal::Timestamp get_time() override;

	/** Turns the auto-post feature on/off. When Auto post is on, post() is executed synchronously */
	void set_auto_post(bool auto_post)
	{
		this->post_is_synchronous_ = auto_post;
	}

	/**	@return true if an action was run. */
	bool run_one();

	/** Calls RunOne() up to some maximum number of times continuing while
		there are still events to dispatch

		@return the number of events dispatched
	*/
	size_t run_many(size_t aMaximum = std::numeric_limits<size_t>::max());

	/** @return The number of active, pending timers and post operations */
	size_t num_active() const
	{
		return post_queue_.size();
	}

	size_t num_pending_timers() const
	{
		return timers_.size();
	}

	openpal::Timestamp next_timer_expiration();

	size_t advance_time(openpal::TimeDuration duration);

	// doesn't check timers_
	void add_time(openpal::TimeDuration duration);

	bool advance_to_next_timer();

private:

	size_t check_for_expired_timers();

	bool find_expired_timer();

	void cancel(openpal::ITimer *timer);

	typedef std::deque<openpal::action_t> post_queue_t;
	typedef std::vector<MockTimer*> timer_vector_t;

	bool post_is_synchronous_;
	openpal::Timestamp current_time_;

	post_queue_t post_queue_;
	timer_vector_t timers_;
};

/** @section desc Test timer class used in conjunction with MockExecutor */
class MockTimer final : public openpal::ITimer
{
	friend class MockExecutor;

public:
	MockTimer(MockExecutor*, const openpal::Timestamp&, const openpal::action_t& action);

	//implement ITimer
	void cancel() override;
	openpal::Timestamp expires_at() override;

private:
	openpal::Timestamp time_;
	MockExecutor* source_;
	openpal::action_t action_;
};

}

#endif

