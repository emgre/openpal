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
#include "openpal/logging/HexLogging.h"

#include "openpal/logging/LogMacros.h"
#include "openpal/util/ToHex.h"
#include "openpal/container/RSlice.h"
#include "openpal/util/Comparisons.h"

namespace openpal
{
	void HexLogging::log(Logger& logger, LogLevel level, const openpal::RSlice& source, char separator, uint32_t first_row_size, uint32_t other_row_size)
	{		
		RSlice copy(source);
		uint32_t row = 0;

		const auto max_first_size = bounded<uint32_t>(first_row_size, 1, max_hex_per_line);
		const auto max_other_size = bounded<uint32_t>(other_row_size, 1, max_hex_per_line);

		while (copy.is_not_empty())
		{
			const auto row_size = (row == 0) ? max_first_size : max_other_size;
			copy = log_line(logger, level, copy, separator, row_size);
			++row;
		}
	}	

	openpal::RSlice HexLogging::log_line(Logger& logger, LogLevel level, const openpal::RSlice& data, char separator, uint32_t max_row_size)
	{
		char buffer[max_log_entry_size];

		uint32_t count = 0;

		while ((count < max_row_size) && (count < data.length())) {
			auto pos = count * 3;
			buffer[pos] = to_hex_char((data[count] & 0xF0) >> 4);
			buffer[pos + 1] = to_hex_char(data[count] & 0x0F);
			buffer[pos + 2] = separator;
			++count;
		}
		
		buffer[(3 * count) - 1] = '\0';

		logger.log(level, LOCATION, buffer);
		
		return data.skip(count);
	}
}

