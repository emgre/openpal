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
#ifndef OPENPAL_ARRAYVIEW_H
#define OPENPAL_ARRAYVIEW_H

#include "HasLength.h"

#include <assert.h>

namespace openpal
{

/**
* Acts as a safe facade around an underlying array
*/
template <class ValueType, class IndexType>
class ArrayView : public HasLength<IndexType>
{

public:

	static ArrayView<ValueType, IndexType> empty_view()
	{
		return ArrayView(nullptr, 0);
	}

	ArrayView(ValueType* start, IndexType length) : HasLength<IndexType>(length), buffer_(start)
	{}

	inline bool contains(IndexType index) const
	{
		return index < this->length_;
	}

	inline bool contains(IndexType start, IndexType stop) const
	{
		return (start < stop) && contains(stop);
	}

	inline ValueType& operator[](IndexType index)
	{
		assert(index < this->length_);
		return buffer_[index];
	}

	inline const ValueType& operator[](IndexType index) const
	{
		assert(index < this->length_);
		return buffer_[index];
	}

	template <class Action>
	void foreach(const Action& action)
	{
		for (IndexType i = 0; i < this->length_; ++i)
		{
			action(buffer_[i]);
		}
	}

	template <class Action>
	void foreach_index(const Action &action)
	{
		for (IndexType i = 0; i < this->length_; ++i)
		{
			action(buffer_[i], i);
		}
	}

private:
	ValueType* buffer_;
};



}

#endif
