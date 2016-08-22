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
#ifndef TESTLIB_LOG_TESTER_H
#define TESTLIB_LOG_TESTER_H

#include <openpal/logging/LogRoot.h>

#include <string>
#include <queue>

namespace openpal
{

struct LogRecord
{
public:

	LogRecord();
	LogRecord(int module, char const* id, LogFilters filters, char const *location, char const *message);
	
	int				moduleid;
	std::string		id;
	openpal::LogFilters	filters;
	std::string		location;
	std::string		message;	
};

class MockLogHandler : public openpal::ILogHandler
{

public:
	MockLogHandler(uint32_t filters = ~0);

	void write_to_stdio();

	void log(const std::string &location, const std::string &msg);

	void log(int module, const char* id, LogFilters filters, char const *location, char const *message) override;

	int32_t pop_filter();

	bool pop_one_entry(int32_t filter);

	bool pop_until(int32_t filter);	
	
	int next_error_code();
	bool get_next_entry(LogRecord &record);
	
	void pop(openpal::ILogHandler &log);

	openpal::LogRoot root;

protected:

	bool output_to_stdio_;
	std::deque<LogRecord> messages_;

};


}

#endif
