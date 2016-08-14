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

LogRecord::LogRecord() :
	id(),
	filters(0),
	location(),
	message(),
	errorCode(-1)
{}

LogRecord::LogRecord(const LogEntry& entry) :
	id(entry.get_alias()),
	filters(entry.get_filters()),
	location(entry.get_location()),
	message(entry.get_message()),
	errorCode(entry.get_error_code())
{

}

MockLogHandler::MockLogHandler(uint32_t filters) :
	root(this, "test", filters),
	output_to_stdio_(false)
{

}


void MockLogHandler::log(const LogEntry &entry)
{
	if (output_to_stdio_)
	{
		std::cout << entry.get_message() << std::endl;
	}

	messages_.push_back(entry);
}

int32_t MockLogHandler::pop_filter()
{
	if (messages_.size() > 0)
	{
		auto flags = messages_.front().filters.get_bitfield();
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
		if (messages_.front().filters.is_set(filter))
		{
			messages_.pop_front();
			return true;
		}
		else return false;
	}
	else return false;
}

bool MockLogHandler::pop_error_code(int code)
{
	while (!messages_.empty())
	{
		bool match = messages_.front().errorCode == code;
		messages_.pop_front();
		if (match)
		{
			return true;
		}
	}

	return false;
}

bool MockLogHandler::pop_until(int32_t filter)
{
	while (!messages_.empty())
	{
		bool match = messages_.front().filters.is_set(filter);
		messages_.pop_front();
		if (match)
		{
			return true;
		}
	}

	return false;
}

int MockLogHandler::clear_log()
{
	int max = -1;
	LogEntry le;
	while (!messages_.empty())
	{
		if (messages_.front().errorCode > max) max = le.get_error_code();
		messages_.pop_front();
	}

	return max;
}

void MockLogHandler::log(const std::string &location, const std::string &message)
{
	root.logger.log(openpal::logflags::EVENT, location.c_str(), message.c_str());
}

void MockLogHandler::write_to_stdio()
{
	this->output_to_stdio_ = true;
}

int MockLogHandler::next_error_code()
{
	LogRecord rec;
	while (!messages_.empty())
	{
		rec = messages_.front();
		messages_.pop_front();
		if (rec.errorCode >= 0)
		{
			return rec.errorCode;
		}
	}
	return -1;
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
	LogRecord record;
	while (get_next_entry(record))
	{
		LogEntry le(record.id.c_str(), record.filters, record.location.c_str(), record.message.c_str(), record.errorCode);
        log.log(le);
	}
}

bool MockLogHandler::is_log_error_free()
{
	return clear_log() < 0;
}

}

