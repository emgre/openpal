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

	LogRoot(int moduleid, ILogHandler* handler, char const* id, LogFilters filters);

	LogRoot(LogRoot&& other);

	LogRoot(const LogRoot&, char const* id);

	~LogRoot();

	const char* get_id() const;

	void rename(char const *id);

	// create another log root, but change the id_
	LogRoot clone(char const *id) const;

	// create another log root, but change the id_ and the filters_
	LogRoot clone(char const *id, LogFilters filters) const;

	bool is_enabled(const LogFilters &rhs) const;

	bool has_any(const LogFilters &filters) const;

	LogFilters get_filters() const;
	
	void log(const LogFilters &filters, char const *location, char const *message);	

	void set_filters(const LogFilters &filters);	

	Logger  logger;

private:

	LogRoot(int moduleid, ILogHandler* pHandler, char const* id, LogFilters filters, bool reuseAlias);

	int				moduleid_;
	ILogHandler*	handler_;
	LogFilters		filters_;   // bit field describing what is being logged
	const char*     id_;

};

}

#endif
