/**
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
#ifndef OPENPAL_HEXLOGGING_H
#define OPENPAL_HEXLOGGING_H

#include "openpal/logging/Logger.h"
#include "openpal/container/RSlice.h"

#include "openpal/util/Uncopyable.h"

namespace openpal
{	
	class HexLogging : private openpal::StaticOnly
	{
		static const uint32_t max_hex_per_line = max_log_entry_size / 3;

	public:
		
		static void log(
			Logger& logger,
			LogLevels levels,		
			const RSlice& source,
			char separator = ' ',
			uint32_t first_row_size = max_hex_per_line,
			uint32_t other_row_size = max_hex_per_line
		);

	private:

		static openpal::RSlice log_line(
			Logger& logger,
			LogLevels levels, 			
			const RSlice& data,
			char separator,
			uint32_t max_row_size
		);
	};

}

#endif
