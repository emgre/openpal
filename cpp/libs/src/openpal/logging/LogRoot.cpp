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

#include "openpal/logging/LogEntry.h"
#include "openpal/logging/LogMacros.h"
#include "openpal/logging/ILogHandler.h"
#include "openpal/logging/LogMacros.h"

#include "openpal/logging/StringCopy.h"

namespace openpal
{

LogRoot::LogRoot(ILogHandler* handler, char const* alias, LogFilters filters) : LogRoot(handler, alias, filters, false)
{

}

LogRoot::LogRoot(ILogHandler* handler, char const* alias, LogFilters filters, bool reuseAlias) :
	logger(this),
	handler_(handler),
	filters_(filters),
	alias_((reuseAlias ? alias : allocate_copy(alias)))
{}

LogRoot::LogRoot(const LogRoot& copy, char const* alias) :
	logger(this),
	handler_(copy.handler_),
	filters_(copy.filters_),
	alias_(allocate_copy(alias))
{

}

LogRoot::LogRoot(LogRoot&& other) : LogRoot(other.handler_, other.alias_, other.filters_, true)
{
	other.alias_ = nullptr;
	other.handler_ = nullptr;
	other.filters_ = 0;
}

LogRoot LogRoot::clone(char const *alias) const
{
	return LogRoot(this->handler_, alias, this->filters_);
}

LogRoot LogRoot::clone(char const *alias, LogFilters filters) const
{
	return LogRoot(this->handler_, alias, filters);
}

LogRoot::~LogRoot()
{
	delete[] alias_;
}

void LogRoot::rename(char const *alias)
{
	delete[] alias_;
	alias_ = allocate_copy(alias);
}

const char* LogRoot::get_id() const
{
	return alias_;
}

void LogRoot::log(const LogFilters &filters, char const *location, char const *message, int error_code)
{
	if (handler_)
	{
		LogEntry le(alias_, filters, location, message, error_code);
        handler_->log(le);
	}
}

bool LogRoot::is_enabled(const LogFilters &rhs) const
{
	return handler_ && (this->filters_ & rhs);
}

bool LogRoot::has_any(const LogFilters &rhs) const
{
	return this->filters_ & rhs;
}

void LogRoot::set_filters(const LogFilters &filters)
{
	filters_ = filters;
}

const LogFilters& LogRoot::get_filters() const
{
	return filters_;
}

}
