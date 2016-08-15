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

