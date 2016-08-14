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
