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

#include "StringFormatting.h"

#include <cstdio>

#ifdef WIN32
#define SAFE_STRING_FORMAT(dest, size, format, ...) _snprintf_s(dest, size, _TRUNCATE, format, ##__VA_ARGS__)
#else
#define SAFE_STRING_FORMAT(dest, size, format, ...) snprintf(dest, size, format, ##__VA_ARGS__)
#endif

#ifdef OPENPAL_CUSTOMIZE_LOGGING

#include "CustomLogMacros.h"

#else

#define SIMPLE_LOG_BLOCK_WITH_CODE(logger, filters, code, message) \
		if(logger.IsEnabled(filters)){ \
			logger.Log(filters, LOCATION, message, code); \
		}

#define SIMPLE_LOGGER_BLOCK_WITH_CODE(pLogger, filters, code, message) \
		if(pLogger && pLogger->IsEnabled(filters)){ \
			pLogger->Log(filters, LOCATION, message, code); \
		}

#define FORMAT_LOG_BLOCK_WITH_CODE(logger, filters, code, format, ...) \
	if(logger.IsEnabled(filters)){ \
		char message[openpal::MAX_LOG_ENTRY_SIZE]; \
		SAFE_STRING_FORMAT(message, openpal::MAX_LOG_ENTRY_SIZE, format, ##__VA_ARGS__); \
		logger.Log(filters, LOCATION, message, code); \
	}

#define FORMAT_LOGGER_BLOCK_WITH_CODE(pLogger, filters, code, format, ...) \
	if(pLogger && pLogger->IsEnabled(filters)){ \
		char message[openpal::MAX_LOG_ENTRY_SIZE]; \
		SAFE_STRING_FORMAT(message, openpal::MAX_LOG_ENTRY_SIZE, format, ##__VA_ARGS__); \
		pLogger->Log(filters, LOCATION, message, code); \
	}

#define FORMAT_HEX_BLOCK(logger, filters, buffer, firstSize, otherSize) \
	if(logger.HasAny(filters)){ \
		LogHex(logger, filters, buffer, firstSize, otherSize); \
	}

#endif

#else

#define SAFE_STRING_FORMAT(dest, size, format, ...)

#define SIMPLE_LOG_BLOCK_WITH_CODE(logger, filters, code, message)

#define SIMPLE_LOGGER_BLOCK_WITH_CODE(pLogger, filters, code, message)

#define FORMAT_LOG_BLOCK_WITH_CODE(logger, filters, code, format, ...)

#define FORMAT_LOGGER_BLOCK_WITH_CODE(pLogger, filters, code, format, ...)

#define FORMAT_HEX_BLOCK(logger, filters, buffer, firstSize, otherSize)

#endif

//macro to remove boiler-plate code for logging messages
#define SIMPLE_LOG_BLOCK(logger, severity, message) \
	SIMPLE_LOG_BLOCK_WITH_CODE(logger, severity, -1, message)

//macro to remove boiler-plate code for logging messages
#define SIMPLE_LOGGER_BLOCK(pLogger, severity, message) \
	SIMPLE_LOGGER_BLOCK_WITH_CODE(pLogger, severity, -1, message)

#define FORMAT_LOGGER_BLOCK(pLogger, filters, format, ...) \
	FORMAT_LOGGER_BLOCK_WITH_CODE(pLogger, filters, -1, format, ##__VA_ARGS__);


#define FORMAT_LOG_BLOCK(logger, filters, format, ...) \
	FORMAT_LOG_BLOCK_WITH_CODE(logger, filters, -1, format, ##__VA_ARGS__);

#endif
