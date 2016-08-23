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
