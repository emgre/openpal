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
#include "openpal/logging/StringFormatting.h"

#include "openpal/logging/LogMacros.h"
#include "openpal/util/ToHex.h"
#include "openpal/container/RSlice.h"
#include "openpal/Configure.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace openpal
{
char* allocate_copy(char const *src)
{
	auto size = strlen(src) + 1;
	char* tmp = new char[size];
#ifdef WIN32
	strcpy_s(tmp, length_, src);
#else
	strcpy(tmp, src);
#endif
	return tmp;
}

void LogHex(Logger& logger, const openpal::LogFilters& filters, const openpal::RSlice& source, uint32_t first_row_size, uint32_t other_row_size)
{
	char buffer[max_log_entry_size];
	RSlice copy(source);
	uint32_t rowCount = 0;
	while (copy.is_not_empty())
	{
		uint32_t rowSize = (copy.length() < max_hex_per_line) ? copy.length() : max_hex_per_line;
		if (rowCount == 0)
		{
			if (first_row_size < rowSize)
			{
				rowSize = first_row_size;
			}
		}
		else
		{
			if (other_row_size < rowSize)
			{
				rowSize = other_row_size;
			}
		}
		auto region = copy.take(rowSize);
		auto pLocation = buffer;
		for (uint32_t pos = 0; pos < rowSize; ++pos)
		{
			pLocation[0] = to_hex_char((region[pos] & 0xf0) >> 4);
			pLocation[1] = to_hex_char(region[pos] & 0xf);
			pLocation[2] = ' ';
			pLocation += 3;
		}
		buffer[3 * rowSize] = '\0';
		copy.advance(rowSize);

        logger.log(filters, "", buffer, -1);

		++rowCount;
	}
}

}

