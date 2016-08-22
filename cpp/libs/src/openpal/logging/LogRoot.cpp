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

LogRoot::LogRoot(int moduleid, ILogHandler* handler, char const* id, LogFilters filters) : 
	LogRoot(moduleid, handler, id, filters, false)
{

}

LogRoot::LogRoot(int moduleid, ILogHandler* handler, char const* id, LogFilters filters, bool reuseAlias) :	
	logger(this),
	moduleid_(moduleid),
	handler_(handler),
	filters_(filters),
	id_((reuseAlias ? id : allocate_copy(id)))
{}

LogRoot::LogRoot(const LogRoot& copy, char const* id) :	
	logger(this),
	moduleid_(copy.moduleid_),
	handler_(copy.handler_),
	filters_(copy.filters_),
	id_(allocate_copy(id))
{

}

LogRoot::LogRoot(LogRoot&& other) : LogRoot(other.moduleid_, other.handler_, other.id_, other.filters_, true)
{
	other.id_ = nullptr;
	other.handler_ = nullptr;
	other.filters_ = 0;
}

LogRoot LogRoot::clone(char const *id) const
{
	return LogRoot(this->moduleid_, this->handler_, id, this->filters_);
}

LogRoot LogRoot::clone(char const *id, LogFilters filters) const
{
	return LogRoot(this->moduleid_, this->handler_, id, filters);
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

void LogRoot::log(const LogFilters &filters, char const *location, char const *message)
{
	if (handler_)
	{		
		handler_->log(moduleid_, id_, filters, location, message);					
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

LogFilters LogRoot::get_filters() const
{
	return filters_;
}

}
