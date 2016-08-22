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
* Interface that represents a distinct logger with an id, module, and levels
*/
class LogRoot : private Uncopyable
{

public:

	LogRoot(LogModule moduleid, ILogHandler* handler, char const* id, LogLevels levels);

	LogRoot(LogRoot&& other);

	LogRoot(const LogRoot&, char const* id);

	~LogRoot();

	const char* get_id() const;

	void rename(char const *id);

	// create another log root, but change the id_
	LogRoot clone(char const *id) const;

	// create another log root, but change the id_ and the levels_
	LogRoot clone(char const *id, LogLevels levels) const;

	bool is_enabled(const LogLevel& level) const;

	bool has_any(const LogLevel& level) const;

	LogLevels get_levels() const;
	
	void log(const LogLevel& level, char const *location, char const *message);	

	void set_levels(const LogLevels& levels);	

	Logger  logger;

private:

	LogRoot(LogModule module, ILogHandler* pHandler, char const* id, LogLevels levels, bool reuseAlias);

	LogModule		module_;
	ILogHandler*	handler_;
	LogLevels		levels_;
	const char*     id_;

};

}

#endif
