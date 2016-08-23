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
#include "openpal/logging/LogRoot.h"

#include "openpal/logging/LogMacros.h"
#include "openpal/logging/ILogHandler.h"
#include "openpal/logging/LogMacros.h"

#include "openpal/logging/StringCopy.h"

namespace openpal
{

LogRoot::LogRoot(ModuleId module, ILogHandler* handler, char const* id, LogLevels levels) :
	LogRoot(module, handler, id, levels, false)
{

}

LogRoot::LogRoot(ModuleId module, ILogHandler* handler, char const* id, LogLevels levels, bool reuseAlias) :
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
