/**
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
#ifndef OPENPAL_LOGROOT_H
#define OPENPAL_LOGROOT_H

#include "LogEntry.h"
#include "Logger.h"
#include "ILogHandler.h"

#include "openpal/util/Uncopyable.h"

namespace openpal
{


/**
* Interface that represents a distinct logger with a name and running level
*/
class LogRoot : private Uncopyable
{

public:

	LogRoot(ILogHandler* handler, char const* alias, LogFilters filters);

	LogRoot(LogRoot&& other);

	LogRoot(const LogRoot&, char const* alias);

	~LogRoot();

	void rename(char const *alias);

	const char* get_id() const;

	void log(const LogFilters &filters, char const *location, char const *message);

	// create another log root, but change the alias_
	LogRoot clone(char const *alias) const;

	// create another log root, but change the alias_ and the filters_
	LogRoot clone(char const *alias, LogFilters filters) const;

	bool is_enabled(const LogFilters &rhs) const;

	bool has_any(const LogFilters &filters) const;

	void set_filters(const LogFilters &filters_);

	const LogFilters& get_filters() const;

	Logger  logger;

private:

	LogRoot(ILogHandler* pHandler, char const* alias, LogFilters filters, bool reuseAlias);

	ILogHandler*	handler_;
	LogFilters		filters_;   // bit field describing what is being logged
	const char*     alias_;

};

}

#endif
