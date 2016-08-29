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

        while ((count < max_row_size) && (count < data.length()))
        {
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

