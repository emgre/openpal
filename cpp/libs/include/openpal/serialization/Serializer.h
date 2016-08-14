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
#ifndef OPENPAL_SERIALIZER_H
#define OPENPAL_SERIALIZER_H

#include <cstdint>

#include "openpal/container/RSlice.h"
#include "openpal/container/WSlice.h"

namespace openpal
{

template <class T>
class Serializer
{
public:

	typedef bool (*read_func_t)(RSlice& buffer, T& output);
	typedef bool (*write_func_t)(const T& value, WSlice& buffer);

	Serializer() : size_(0), read_func_(nullptr), write_func(nullptr)
	{}

	Serializer(uint32_t size_, read_func_t read_func, write_func_t write_func) :
		size_(size_), read_func_(read_func), write_func(write_func)
	{}

	/**
	* @return The size (in bytes) required for every call to read/write
	*/
	uint32_t size() const
	{
		return size_;
	}

	/**
	* reads the value and advances the read buffer
	*/
	bool read(RSlice &buffer, T &output) const
	{
		return (*read_func_)(buffer, output);
	}

	/**
	* writes the value and advances the write buffer
	*/
	bool write(const T &value, WSlice &buffer) const
	{
		return (*write_func)(value, buffer);
	}

private:

	uint32_t size_;
	read_func_t read_func_;
	write_func_t write_func;

};

}

#endif
