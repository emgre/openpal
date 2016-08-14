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
#ifndef OPENPAL_LOGENTRY_H
#define OPENPAL_LOGENTRY_H

#include <cstdint>

#include "LogFilters.h"

namespace openpal
{

/**
* An event recorded by the logging framework
*/
class LogEntry
{

public:

	LogEntry();

	LogEntry(char const* alias, const LogFilters& filters, char const* location, char const* message, int error_code);

	/// @return The alias of the logger that recorded the message
	inline char const* get_alias() const
	{
		return alias_;
	}

	/// @return The place in the source code where the message was recorded
	inline char const* get_location() const
	{
		return location_;
	}

	/// @return body of the log message
	inline char const* get_message() const
	{
		return message_;
	}

	/// @return the log level of the message
	inline const LogFilters& get_filters() const
	{
		return filters_;
	}

	/// @return the error code associated with the message
	inline int	get_error_code() const
	{
		return error_code_;
	}

private:

	char const*		alias_;
	LogFilters		filters_;
	char const*		location_;
	char const*		message_;
	int				error_code_;
};

}

#endif
