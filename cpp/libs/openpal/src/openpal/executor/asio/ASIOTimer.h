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

#include "openpal/executor/ITimer.h"

#include "openpal/util/Uncopyable.h"

#include <asio.hpp>

namespace openpal
{

    class ASIOTimer final : public openpal::ITimer, private openpal::Uncopyable
    {
        friend class Executor;

    public:

        ASIOTimer(const std::shared_ptr<asio::io_service>& io_service) :
            impl(*io_service),
            io_service(io_service)
        {}

        static std::shared_ptr<ASIOTimer> create(const std::shared_ptr<asio::io_service>& io_service)
        {
            return std::make_shared<ASIOTimer>(io_service);
        }

        virtual void cancel() override
        {
            std::error_code ec;
            impl.cancel(ec);
        }

        virtual steady_time_t expires_at() override
        {
            return impl.expires_at();
        }

        asio::basic_waitable_timer<std::chrono::steady_clock> impl;

    private:

        const std::shared_ptr<asio::io_service> io_service;
    };

}



