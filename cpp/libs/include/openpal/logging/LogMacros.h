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
#ifndef OPENPAL_LOGMACROS_H
#define OPENPAL_LOGMACROS_H

#include "Location.h"

#ifndef OPENPAL_STRIP_LOGGING

#include "HexLogging.h"

#include <cstdio>

#ifdef WIN32
#define SAFE_STRING_FORMAT(dest, length_, format, ...) _snprintf_s(dest, length_, _TRUNCATE, format, ##__VA_ARGS__)
#else
#define SAFE_STRING_FORMAT(dest, size, format, ...) snprintf(dest, size, format, ##__VA_ARGS__)
#endif

#ifdef OPENPAL_CUSTOMIZE_LOGGING

#include "CustomLogMacros.h"

#else

#define LOG_FORMAT(logger, levels, format, ...) { \
	char message[openpal::max_log_entry_size]; \
	SAFE_STRING_FORMAT(message, openpal::max_log_entry_size, format, ##__VA_ARGS__); \
	logger.log(levels, LOCATION, message); } \

#define SIMPLE_LOG_BLOCK(logger, levels, message) \
		if(logger.is_enabled(levels)){ \
			logger.log(levels, LOCATION, message); \
		}

#define SIMPLE_LOGGER_BLOCK(pLogger, levels, message) \
		if(pLogger && pLogger->is_enabled(levels)){ \
			pLogger->log(levels, LOCATION, message); \
		}

#define FORMAT_LOG_BLOCK(logger, levels, format, ...) \
	if(logger.is_enabled(levels)){ \
		char message[openpal::max_log_entry_size]; \
		SAFE_STRING_FORMAT(message, openpal::max_log_entry_size, format, ##__VA_ARGS__); \
		logger.log(levels, LOCATION, message); \
	}

#define FORMAT_LOGGER_BLOCK(pLogger, levels, format, ...) \
	if(pLogger && pLogger->is_enabled(levels)){ \
		char message[openpal::max_log_entry_size]; \
		SAFE_STRING_FORMAT(message, openpal::max_log_entry_size, format, ##__VA_ARGS__); \
		pLogger->log(levels, LOCATION, message); \
	}

#define FORMAT_HEX_BLOCK(logger, levels, buffer, firstSize, otherSize) \
	if(logger.has_any(levels)){ \
		hex::log(logger, levels, buffer, firstSize, otherSize); \
	}

#endif

#else

#define SAFE_STRING_FORMAT(dest, length_, format, ...)

#define SIMPLE_LOG_BLOCK_WITH_CODE(logger, levels_, code, message_)

#define SIMPLE_LOGGER_BLOCK_WITH_CODE(pLogger, levels_, code, message_)

#define FORMAT_LOG_BLOCK_WITH_CODE(logger, levels_, code, format, ...)

#define FORMAT_LOGGER_BLOCK_WITH_CODE(pLogger, levels_, code, format, ...)

#define FORMAT_HEX_BLOCK(logger, levels_, buffer_, firstSize, otherSize)

#endif

/*
//macro to remove boiler-plate code for logging messages_
#define SIMPLE_LOG_BLOCK(logger, severity, message) \
	SIMPLE_LOG_BLOCK_WITH_CODE(logger, severity, message)

//macro to remove boiler-plate code for logging messages_
#define SIMPLE_LOGGER_BLOCK(pLogger, severity, message) \
	SIMPLE_LOGGER_BLOCK_WITH_CODE(pLogger, severity, message)

#define FORMAT_LOGGER_BLOCK(pLogger, levels, format, ...) \
	FORMAT_LOGGER_BLOCK_WITH_CODE(pLogger, levels, format, ##__VA_ARGS__);


#define FORMAT_LOG_BLOCK(logger, levels, format, ...) \
	FORMAT_LOG_BLOCK_WITH_CODE(logger, levels, format, ##__VA_ARGS__);
*/

#endif
