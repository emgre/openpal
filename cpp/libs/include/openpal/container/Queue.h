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
#ifndef OPENPAL_QUEUE_H
#define OPENPAL_QUEUE_H

#include <assert.h>

#include "openpal/container/Array.h"

namespace openpal
{

template <class ValueType, class IndexType>
class Queue
{

public:

	Queue(IndexType size) : count_(0), first_(0), next_insert_(0), buffer_(size)
	{}

	IndexType size() const
	{
		return count_;
	}

	IndexType capacity() const
	{
		return buffer_.length();
	}

	bool is_empty() const
	{
		return count_ == 0;
	}

	bool is_not_empty() const
	{
		return count_ > 0;
	}

	bool is_full() const
	{
		return count_ == buffer_.length();
	}

	void clear()
	{
		count_ = first_ = next_insert_ = 0;
	}

	ValueType* peek()
	{
		if (is_empty())
		{
			return nullptr;
		}
		else
		{
			return &buffer_[first_];
		}
	}

	ValueType* pop()
	{
		if (is_empty())
		{
			return nullptr;
		}
		else
		{
			IndexType ret = first_;
			first_ = (first_ + 1) % buffer_.length();
			--count_;
			return &buffer_[ret];
		}
	}

	bool enqueue(const ValueType &value)
	{
		if (is_full())
		{
			return false;
		}
		else
		{
			buffer_[next_insert_] = value;
			next_insert_ = (next_insert_ + 1) % buffer_.length();
			++count_;
			return true;
		}
	}

private:

	IndexType count_;
	IndexType first_;
	IndexType next_insert_;

	openpal::Array<ValueType, IndexType> buffer_;
};

}

#endif
