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

#include "openpal/executor/asio/StrandExecutor.h"

#include "ASIOTimer.h"

namespace openpal
{

    Timer StrandExecutor::start(const duration_t& duration, const action_t& action)
    {
        return this->start(get_time() + duration, action);
    }

    Timer StrandExecutor::start(const steady_time_t& expiration, const action_t& action)
    {
        const auto timer = ASIOTimer::create(this->io_service);

        timer->impl.expires_at(expiration);

        // neither this executor nor the timer can be deleted while the timer is still active
        auto callback = [timer, action, self = shared_from_this()](const std::error_code & ec)
        {
            if (!ec)   // an error indicate timer was canceled
            {
                action();
            }
        };

        timer->impl.async_wait(strand.wrap(callback));

        return Timer(timer);
    }

    void StrandExecutor::post(const action_t& action)
    {
        auto callback = [action, self = shared_from_this()]()
        {
            action();
        };

        strand.post(callback);
    }

    steady_time_t StrandExecutor::get_time()
    {
        return std::chrono::steady_clock::now();
    }

}



