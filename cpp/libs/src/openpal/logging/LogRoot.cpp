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
#include "openpal/logging/LogRoot.h"

#include "openpal/logging/LogMacros.h"
#include "openpal/logging/ILogHandler.h"
#include "openpal/logging/LogMacros.h"

#include "openpal/logging/StringCopy.h"

namespace openpal
{

LogRoot::LogRoot(LogModule module, ILogHandler* handler, char const* id, LogLevels levels) :
	LogRoot(module, handler, id, levels, false)
{

}

LogRoot::LogRoot(LogModule module, ILogHandler* handler, char const* id, LogLevels levels, bool reuseAlias) :
	logger(this),
	module_(module),
	handler_(handler),
	levels_(levels),
	id_((reuseAlias ? id : allocate_copy(id)))
{}

LogRoot::LogRoot(const LogRoot& copy, char const* id) :	
	logger(this),
	module_(copy.module_),
	handler_(copy.handler_),
	levels_(copy.levels_),
	id_(allocate_copy(id))
{

}

LogRoot::LogRoot(LogRoot&& other) : LogRoot(other.module_, other.handler_, other.id_, other.levels_, true)
{
	other.id_ = nullptr;
	other.handler_ = nullptr;
	other.levels_ = LogLevels(0);
}

LogRoot LogRoot::clone(char const *id) const
{
	return LogRoot(this->module_, this->handler_, id, this->levels_);
}

LogRoot LogRoot::clone(char const *id, LogLevels levels) const
{
	return LogRoot(this->module_, this->handler_, id, levels);
}

LogRoot::~LogRoot()
{
	delete[] id_;
}

void LogRoot::rename(char const *id)
{
	delete[] id_;
	id_ = allocate_copy(id);
}

const char* LogRoot::get_id() const
{
	return id_;
}

void LogRoot::log(const LogLevel& level, char const *location, char const *message)
{
	if (handler_)
	{		
		handler_->log(module_, id_, level, location, message);					
	}
}

bool LogRoot::is_enabled(const LogLevel& level) const
{
	return handler_ && (this->levels_.is_set(level));
}

bool LogRoot::has_any(const LogLevel& level) const
{
	return this->levels_.is_set(level);
}

void LogRoot::set_levels(const LogLevels &levels)
{
	levels_ = levels;
}

LogLevels LogRoot::get_levels() const
{
	return levels_;
}

}
