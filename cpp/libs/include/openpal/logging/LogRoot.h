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

	LogRoot(ModuleId moduleid, ILogHandler* handler, char const* id, LogLevels levels);

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

	LogRoot(ModuleId module, ILogHandler* pHandler, char const* id, LogLevels levels, bool reuseAlias);

	ModuleId		module_;
	ILogHandler*	handler_;
	LogLevels		levels_;
	const char*     id_;

};

}

#endif
