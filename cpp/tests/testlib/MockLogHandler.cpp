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
#include "MockLogHandler.h"

#include <openpal/logging/LogLevels.h>

#include <iostream>

using namespace openpal;

namespace openpal
{

LogRecord::LogRecord() : level(0)		
{}

LogRecord::LogRecord(ModuleId module, char const* id, LogLevel level, char const *location, char const *message) :
	module(module),
	id(id),
	level(level),
	location(location),
	message(message)
{

}

MockLogHandler::MockLogHandler(LogLevels levels) :
	root(ModuleId(0), this, "test", levels),
	output_to_stdio_(false)
{

}


void MockLogHandler::log(ModuleId module, const char* id, LogLevel level, char const *location, char const *message)
{
	if (output_to_stdio_)
	{
		std::cout << message << std::endl;
	}

	messages_.push_back(
		LogRecord(module, id, level, location, message)
	);
}

int32_t MockLogHandler::pop_filter()
{
	if (messages_.size() > 0)
	{
		auto flags = messages_.front().level.value;
		messages_.pop_front();
		return flags;
	}
	else
	{
		return 0;
	}
}

bool MockLogHandler::pop_one_entry(int32_t filter)
{
	if (messages_.size() == 1)
	{
		if ((messages_.front().level.value & filter) != 0)
		{
			messages_.pop_front();
			return true;
		}
		else return false;
	}
	else return false;
}

bool MockLogHandler::pop_until(int32_t filter)
{
	while (!messages_.empty())
	{
		bool match = (messages_.front().level.value & filter) != 0;
		messages_.pop_front();
		if (match)
		{
			return true;
		}
	}

	return false;
}

void MockLogHandler::log(const std::string &location, const std::string &message)
{
	root.logger.log(openpal::levels::event, location.c_str(), message.c_str());
}

void MockLogHandler::write_to_stdio()
{
	this->output_to_stdio_ = true;
}

bool MockLogHandler::get_next_entry(LogRecord &record)
{
	if (messages_.empty()) return false;
	else
	{
		record = messages_.front();
		messages_.pop_front();
		return true;
	}
}

void MockLogHandler::pop(openpal::ILogHandler &log)
{
	LogRecord rec;
	while (get_next_entry(rec))
	{		
		log.log(rec.module, rec.id.c_str(), rec.level, rec.location.c_str(), rec.message.c_str());
	}
}

}

