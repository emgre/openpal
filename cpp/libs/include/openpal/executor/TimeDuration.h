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
#ifndef OPENPAL_TIMEDURATION_H
#define OPENPAL_TIMEDURATION_H

#include <cstdint>

namespace openpal
{

template <class T>
class TimeDurationBase
{

public:

	T get_milliseconds() const
	{
		return milliseconds_;
	}

	bool is_negative() const
	{
		return milliseconds_ < 0;
	}

	bool is_postive() const
	{
		return milliseconds_ > 0;
	}

	operator T() const
	{
		return milliseconds_;
	}

protected:

	TimeDurationBase() : milliseconds_(0)
	{}

	TimeDurationBase(T milliseconds) : milliseconds_(milliseconds)
	{}

	T milliseconds_;
};


/**
*  Strong typing for millisecond based time durations
*/
class TimeDuration : public TimeDurationBase<int64_t>
{

public:

	TimeDuration();

	static TimeDuration min_value();

	static TimeDuration max_value();

	static TimeDuration zero_value();

	static TimeDuration milliseconds(int64_t milliseconds);

	static TimeDuration seconds(int64_t seconds);

	static TimeDuration minutes(int64_t minutes);

	static TimeDuration hours(int64_t hours);

	static TimeDuration days(int64_t days);

private:

	TimeDuration(int64_t milliseconds);
};

bool operator==(const TimeDuration& lhs, const TimeDuration& rhs);

}

#endif
