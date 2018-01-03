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

#ifndef OPENPAL_ASIO_THREADPOOL_H
#define OPENPAL_ASIO_THREADPOOL_H

#include <functional>
#include <chrono>
#include <thread>

#include <asio.hpp>

namespace openpal
{

    /**
    *	A thread pool that calls asio::io_service::run
    */
    class ThreadPool
    {
    public:

        typedef std::function<void(uint32_t)> thread_init_t;

        ThreadPool(
            const std::shared_ptr<asio::io_service>& io_service,
            uint32_t concurrency
        );

        ThreadPool(
            const std::shared_ptr<asio::io_service>& io_service,
            uint32_t concurrency,
            const thread_init_t& on_thread_start,
            const thread_init_t& on_thread_exit
        );

        ~ThreadPool();

        void shutdown();

    private:

        const std::shared_ptr<asio::io_service> io_service;

        thread_init_t on_thread_start;
        thread_init_t on_thread_exit;

        bool is_shutdown = false;

        void run(uint32_t threadnum);

        asio::basic_waitable_timer< std::chrono::steady_clock> infinite_timer;
        std::vector<std::unique_ptr<std::thread>> threads;
    };


}

#endif

