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
#include "openpal/executor/TimeDuration.h"

#include "openpal/util/Limits.h"

namespace openpal
{

TimeDuration TimeDuration::min_value()
{
	return TimeDuration(openpal::min_value<int64_t>());
}

TimeDuration TimeDuration::max_value()
{
	return TimeDuration(openpal::max_value<int64_t>());
}

TimeDuration TimeDuration::zero_value()
{
	return TimeDuration(0);
}

TimeDuration TimeDuration::milliseconds(int64_t milliseconds)
{
	return TimeDuration(milliseconds);
}

TimeDuration TimeDuration::seconds(int64_t seconds)
{
	return TimeDuration(1000 * seconds);
}

TimeDuration TimeDuration::minutes(int64_t minutes)
{
	return TimeDuration(static_cast<int64_t>(1000 * 60) * minutes);
}

TimeDuration TimeDuration::hours(int64_t hours)
{
	return TimeDuration(static_cast<int64_t>(1000 * 60 * 60) * hours);
}

TimeDuration TimeDuration::days(int64_t days)
{
	return TimeDuration(static_cast<int64_t>(1000 * 60 * 60 * 24) * days);
}

TimeDuration::TimeDuration() : TimeDurationBase(0) {}

TimeDuration::TimeDuration(int64_t milliseconds) : TimeDurationBase(milliseconds)
{}

bool operator==(const TimeDuration& lhs, const TimeDuration& rhs)
{
	return lhs.get_milliseconds() == rhs.get_milliseconds();
}

}
