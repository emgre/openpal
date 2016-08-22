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
#include "MockLogHandler.h"

#include <openpal/logging/LogLevels.h>

#include <iostream>

using namespace openpal;

namespace openpal
{

LogRecord::LogRecord() : levels(0)		
{}

LogRecord::LogRecord(int module, char const* id, LogLevels levels, char const *location, char const *message) :
	moduleid(moduleid),
	id(id),
	levels(levels),
	location(location),
	message(message)
{

}

MockLogHandler::MockLogHandler(uint32_t levels) :
	root(0, this, "test", levels),
	output_to_stdio_(false)
{

}


void MockLogHandler::log(int module, const char* id, LogLevels levels, char const *location, char const *message)
{
	if (output_to_stdio_)
	{
		std::cout << message << std::endl;
	}

	messages_.push_back(
		LogRecord(module, id, levels, location, message)
	);
}

int32_t MockLogHandler::pop_filter()
{
	if (messages_.size() > 0)
	{
		auto flags = messages_.front().levels.levels();
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
		if (messages_.front().levels.is_set(filter))
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
		bool match = messages_.front().levels.is_set(filter);
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
	root.logger.log(openpal::levels::EVENT, location.c_str(), message.c_str());
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
		log.log(rec.moduleid, rec.id.c_str(), rec.levels, rec.location.c_str(), rec.message.c_str());
	}
}

}

