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
#ifndef TESTLIB_LOG_TESTER_H
#define TESTLIB_LOG_TESTER_H

#include "openpal/logging/Logger.h"

#include <string>
#include <queue>
#include <memory>

namespace openpal
{

    struct LogRecord
    {

    public:

        LogRecord();
        LogRecord(ModuleId module, char const* id, LogLevel level, char const* location, char const* message);

        ModuleId		module;
        std::string		id;
        openpal::LogLevel level;
        std::string		location;
        std::string		message;
    };

    class MockLogHandler
    {
		struct Backend final : public openpal::ILogHandler
		{
			void log(ModuleId module, const char* id, LogLevel level, char const* location, char const* message) override;			

			bool output_to_stdio = false;
			std::deque<LogRecord> messages;

			std::vector<std::shared_ptr<openpal::ILogHandler>> handlers;
		};

    public:

        MockLogHandler(LogLevels levels = LogLevels(0));

        void write_to_stdio();

		void log_everything();

        void log(const std::string& location, const std::string& msg);        

        void pop(openpal::ILogHandler& log);

		void add_backend(const std::shared_ptr<ILogHandler>& dest)
		{
			backend->handlers.push_back(dest);
		}

    protected:

		const std::shared_ptr<Backend> backend;

	public:

		openpal::Logger logger;

    };


}

#endif
