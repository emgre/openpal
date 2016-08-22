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
#ifndef OPENPAL_LOGLEVELS_H
#define OPENPAL_LOGLEVELS_H

#include <cstdint>

namespace openpal
{

struct ModuleId
{

public:

	ModuleId() : value(0)
	{}

	explicit ModuleId(int32_t level) : value(level)
	{}

	int32_t	value;
};

struct LogLevel
{

public:

	LogLevel() : value(0)
	{}

	explicit LogLevel(int32_t level) : value(level)
	{}

	int32_t	value;
};

// some default log flags
namespace levels
{
	const LogLevel EVENT = LogLevel(1 << 0);
	const LogLevel ERR = LogLevel(1 << 1);
	const LogLevel WARN = LogLevel(1 << 2);
	const LogLevel INFO = LogLevel(1 << 3);
	const LogLevel DBG = LogLevel(1 << 4);
}

/**
* Strongly typed wrapper for flags bitfield
*/
class LogLevels
{

public:

	LogLevels() : levels_(0)
	{}

	explicit LogLevels(int32_t levels) : levels_(levels)
	{}

	static LogLevels everything() {
		return LogLevels(~0);
	}

	inline bool is_set(const LogLevel& level) const
	{
		return (level.value & levels_) != 0;
	}	

	int32_t levels() const
	{
		return levels_;
	}

private:

	int32_t	levels_;
};

}

#endif
