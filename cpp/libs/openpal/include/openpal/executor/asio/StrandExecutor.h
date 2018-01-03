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
#ifndef OPENPAL_ASIO_STRANDEXECUTOR_H
#define OPENPAL_ASIO_STRANDEXECUTOR_H

#include "openpal/executor/IExecutor.h"
#include "openpal/util/Uncopyable.h"

#include <asio.hpp>

namespace openpal
{

    /**
    *
    * Implementation of openpal::IExecutor backed by asio::strand
    *
    * Shutdown life-cycle guarantees are provided by using std::shared_ptr
    *
    */
    class StrandExecutor final :
        public openpal::IExecutor,
        public std::enable_shared_from_this<StrandExecutor>,
        private openpal::Uncopyable
    {

    public:

		StrandExecutor(const std::shared_ptr<asio::io_service>& io_service) :
            io_service(io_service),
            strand(*io_service)
        {}

        static std::shared_ptr<StrandExecutor> create(const std::shared_ptr<asio::io_service>& io_service)
        {
            return std::make_shared<StrandExecutor>(io_service);
        }

        std::shared_ptr<StrandExecutor> fork()
        {
            return create(this->io_service);
        }

        // ---- Implement IExecutor -----

        virtual Timer start(const duration_t& duration, const action_t& action) override;
        virtual Timer start(const steady_time_t& expiration, const action_t& action) override;
        virtual void post(const action_t& action) override;
        virtual steady_time_t get_time() override;

    private:

        // we hold a shared_ptr to the io_service so that it cannot dissapear while the strand is still executing
        const std::shared_ptr<asio::io_service> io_service;

	public:

        asio::strand strand;
    };


}

#endif

