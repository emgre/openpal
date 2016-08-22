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
