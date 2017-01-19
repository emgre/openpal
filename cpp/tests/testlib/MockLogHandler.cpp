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

    LogRecord::LogRecord(ModuleId module, char const* id, LogLevel level, char const* location, char const* message) :
        module(module),
        id(id),
        level(level),
        location(location),
        message(message)
    {

    }

    MockLogHandler::MockLogHandler(LogLevels levels) :
		backend(std::make_shared<Backend>()),
		logger(backend, ModuleId(0), "test", levels)
    {

    }


    void MockLogHandler::Backend::log(ModuleId module, const char* id, LogLevel level, char const* location, char const* message)
    {		
		if (output_to_stdio)
		{
			std::cout << message << std::endl;
		}

		for (auto& handler : handlers)
		{
			handler->log(module, id, level, location, message);
		}

		if (save_messages)
		{
			messages.push_back(LogRecord(module, id, level, location, message));
		}		
    }
   
    void MockLogHandler::log(const std::string& location, const std::string& message)
    {
        backend->log(ModuleId(0), "test", openpal::levels::event, location.c_str(), message.c_str());
    }

    void MockLogHandler::write_to_stdio()
    {
        this->backend->output_to_stdio = true;
    }

	void MockLogHandler::log_everything()
	{
		this->logger.set_levels(LogLevels(~0));
	}

    void MockLogHandler::pop(openpal::ILogHandler& log)
    {        
		for (auto& rec : backend->messages)
		{
			log.log(rec.module, rec.id.c_str(), rec.level, rec.location.c_str(), rec.message.c_str());
		}

		backend->messages.clear();
    }

}

