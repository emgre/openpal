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
	bool start(const TimeDuration &timeout, const action_t &action);
	bool start(const Timestamp &expiration, const action_t &action);

	// start a new timer, canceling any existing timer
	void restart(const TimeDuration &expiration, const action_t &action);
	void restart(const Timestamp &expiration, const action_t &action);

private:

	IExecutor* executor_;
	ITimer* timer_;
};

}

#endif
