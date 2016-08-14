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
#ifndef OPENPAL_STRINGFORMATTING_H
#define OPENPAL_STRINGFORMATTING_H

#include "Logger.h"

namespace openpal
{
class RSlice;

const uint32_t max_log_entry_size = 120;
const uint32_t max_hex_per_line = 20;

static_assert(max_hex_per_line < (max_log_entry_size / 3), "Each hex byte takes 3 characters");

void LogHex(Logger& logger, const openpal::LogFilters& filters, const openpal::RSlice& source, uint32_t first_row_size, uint32_t other_row_size);

// Portable allocation of a copy of a cstring
char* allocate_copy(char const *alias);

}

#endif
