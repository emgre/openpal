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

#include <queue>
#include <limits>
#include <memory>
#include <cstddef>

namespace openpal
{

    class MockTimer;

    /** @section desc Test class that doles out MockTimer* */
    class MockExecutor final : public IExecutor
    {
        friend class MockTimer;

    public:

		static std::shared_ptr<MockExecutor> Create()
		{
			return std::make_shared<MockExecutor>();
		}

        // Implement IExecutor
        virtual Timer start(const duration_t&, const action_t& action) override;
        virtual Timer start(const steady_time_t&, const action_t& action) override;
        virtual void post(const action_t& action) override;
        virtual steady_time_t get_time() override;

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
            return this->post_queue.size();
        }

        size_t num_pending_timers() const
        {
            return this->timers.size();
        }

		steady_time_t next_timer_expiration_abs() const;

		steady_time_t next_timer_expiration_rel() const;

        size_t advance_time(duration_t duration);

        // doesn't check timers_
        void add_time(duration_t duration);

        bool advance_to_next_timer();

		size_t num_timer_cancel() const {
			return this->num_timer_cancel_;
		}

    private:

        size_t check_for_expired_timers();

		size_t num_timer_cancel_ = 0;

        bool find_expired_timer();

        void cancel(ITimer* timer);

        typedef std::deque<action_t> post_queue_t;
        typedef std::vector<std::shared_ptr<MockTimer>> timer_vector_t;
		
		steady_time_t current_time;

        post_queue_t post_queue;
        timer_vector_t timers;
    };

    /** @section desc Test timer class used in conjunction with MockExecutor */
    class MockTimer final : public ITimer
    {
        friend class MockExecutor;

    public:
        MockTimer(MockExecutor*, const steady_time_t&, const action_t& action);

        // implement ITimer
        void cancel() override;
		steady_time_t expires_at() override;

    private:
		steady_time_t time;
        MockExecutor* source;
        action_t action;
    };

}

#endif

