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
#ifndef OPENPAL_SERIALIZATIONTEMPLATESLE_H
#define OPENPAL_SERIALIZATIONTEMPLATESLE_H

#include <cstdint>
#include <cstring>

#include "openpal/container/RSlice.h"
#include "openpal/container/WSlice.h"

#include "openpal/util/Limits.h"

namespace openpal
{

template <class T>
class Bit16LE
{
public:

	static T read(const uint8_t *data)
	{
		return (static_cast<T>(data[0]) << 0) | (static_cast<T>(data[1]) << 8);
	}

	static void write(uint8_t *data, T value)
	{
		data[0] = static_cast<uint8_t>(value & 0xFF);
		data[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
	}

	static void write_to_slice(WSlice &dest, T value)
	{
		write(dest, value);
		dest.advance(size);
	}

	inline static T read_from_slice(RSlice &slice)
	{
		auto ret = read(slice);
        slice.advance(size);
		return ret;
	}

	typedef T type_t;

	const static size_t size = sizeof(T);
	const static T max_value;
	const static T min_value;
};

template <class T>
const T Bit16LE<T>::max_value = openpal::max_value<T>();

template <class T>
const T Bit16LE<T>::min_value = openpal::min_value<T>();

template <class T>
class Bit32LE
{
public:

	// Endianness doesn't apply to everything. If you do bitwise or bitshift operations on an int, you don't notice the endianness.
	// The machine arranges the multiple bytes, so the least significant byte is still the least significant byte, and the most
	// significant byte is still the most significant byte

	// This is endian independent of the machine order
	static T read(const uint8_t *data)
	{
		return	(static_cast<T>(data[0]) << 0)	|
		        (static_cast<T>(data[1]) << 8)	|
		        (static_cast<T>(data[2]) << 16) |
		        (static_cast<T>(data[3]) << 24);
	}

	static void write(uint8_t *data, T value)
	{
		data[0] = static_cast<uint8_t>(value & 0xFF);
		data[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
		data[2] = static_cast<uint8_t>((value >> 16) & 0xFF);
		data[3] = static_cast<uint8_t>((value >> 24) & 0xFF);
	}

	static void write_to_slice(WSlice& dest, T value)
	{
		write(dest, value);
		dest.advance(size);
	}

	inline static T read_from_slice(RSlice &buffer)
	{
		auto ret = read(buffer);
        buffer.advance(size);
		return ret;
	}

	typedef T type_t;

	const static size_t size = sizeof(T);
	const static T max_value;
	const static T min_value;
};

template <class T>
const T Bit32LE<T>::max_value = openpal::max_value<T>();

template <class T>
const T Bit32LE<T>::min_value = openpal::min_value<T>();

}

#endif
