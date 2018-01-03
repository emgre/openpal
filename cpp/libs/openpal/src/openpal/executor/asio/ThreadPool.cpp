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

#include "openpal/executor/asio/ThreadPool.h"

namespace openpal
{

    ThreadPool::ThreadPool(
        const std::shared_ptr<asio::io_service>& io_service,
        uint32_t concurrency
    ) :
        ThreadPool(
            io_service,
            concurrency,
            [](uint32_t) {},
    [](uint32_t) {}
    )
    {}

    ThreadPool::ThreadPool(
        const std::shared_ptr<asio::io_service>& io_service,
        uint32_t concurrency,
        const thread_init_t& on_thread_start,
        const thread_init_t& on_thread_exit) :
        io_service(io_service),
        on_thread_start(on_thread_start),
        on_thread_exit(on_thread_exit),
        infinite_timer(*io_service)
    {
        if (concurrency == 0)
        {
            concurrency = 1;
        }

        infinite_timer.expires_at(std::chrono::steady_clock::time_point::max());
        infinite_timer.async_wait([](const std::error_code&) {});

        for (uint32_t i = 0; i < concurrency; ++i)
        {
            auto run = [this, i]()
            {
                this->run(i);
            };
            threads.push_back(std::make_unique<std::thread>(run));
        }
    }

    ThreadPool::~ThreadPool()
    {
        this->shutdown();
        threads.clear();
    }

    void ThreadPool::shutdown()
    {
        if (!this->is_shutdown)
        {
            this->is_shutdown = true;
            this->infinite_timer.cancel();
            for (auto& thread : threads)
            {
                thread->join();
            }
        }
    }

    void ThreadPool::run(uint32_t threadnum)
    {
        this->on_thread_start(threadnum);

        this->io_service->run();

        this->on_thread_exit(threadnum);
    }

}



