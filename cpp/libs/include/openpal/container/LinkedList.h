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
#ifndef OPENPAL_LINKEDLIST_H
#define OPENPAL_LINKEDLIST_H

#include "ArrayView.h"

#include "openpal/container/Array.h"

namespace openpal
{

template <class ValueType>
class ListNode
{
public:
	ListNode() : value(), prev_(nullptr), next_(nullptr)
	{}

	ValueType value;

private:
	ListNode* prev_;
	ListNode* next_;

	template <class T, class U>
	friend class LinkedList;

	template <class T>
	friend class LinkedListIterator;
};


template <class ValueType>
class LinkedListIterator
{
public:
	static LinkedListIterator<ValueType> undefined()
	{
		return LinkedListIterator(nullptr);
	}

	static LinkedListIterator<ValueType> from(ListNode<ValueType> *start)
	{
		return LinkedListIterator(start);
	}

	bool has_next() const
	{
		return (current_ != nullptr);
	}

	ListNode< ValueType>* next()
	{
		if (current_ == nullptr)
		{
			return nullptr;
		}
		else
		{
			auto pRet = current_;
			current_ = current_->next_;
			return pRet;
		}
	}

	ListNode< ValueType>* current()
	{
		return current_;
	}

	ValueType* current_value()
	{
		if (current_)
		{
			return &current_->value;
		}
		else
		{
			return nullptr;
		}
	}

private:

	LinkedListIterator(ListNode< ValueType>* start) : current_(start)
	{}

	ListNode<ValueType>* current_;
};


// A container adapter for a -linked list
template <class ValueType, class IndexType>
class LinkedList : public HasLength<IndexType>, private openpal::Uncopyable
{
public:

	typedef LinkedListIterator<ValueType> Iterator;

	LinkedList(IndexType max_size) :
		HasLength<IndexType>(0),
		head_(nullptr),
		tail_(nullptr),
		free_(nullptr),
		underlying(max_size)
	{
		initialize();
	}

	IndexType capacity() const
	{
		return underlying.length();
	}

	void clear()
	{
		if (this->is_not_empty())
		{
			// link the remaining free list to the end of active list
			this->link(tail_, free_);
			// set the free pointer to the head_
			free_ = head_;
			head_ = tail_ = nullptr;
			this->length_ = 0;
		}
	}

	inline ListNode<ValueType>* head()
	{
		return head_;
	}

	Iterator iterate() const
	{
		return Iterator::from(head_);
	}

	template <class Selector>
	ListNode<ValueType>* find_first(Selector select);

	ListNode<ValueType>* add(const ValueType &value);

	template <class Selector>
	void select_while(Selector select)
	{
		auto iter = this->iterate();
		bool result = true;
		while (result && iter.has_next())
		{
			result = select(iter.next()->value);
		}
	}

	template <class Selector>
	void foreach(Selector select)
	{
		auto iter = this->iterate();
		while (iter.has_next())
		{
			select(iter.next()->value);
		}
	}

	template <class Selector>
	ListNode<ValueType>* remove_first(Selector select)
	{
		auto pNode = this->find_first(select);
		if (pNode)
		{
			this->remove(pNode);
		}
		return pNode;
	}

	template <class Selector>
	IndexType remove_all(Selector match)
	{
		IndexType count = 0;

		auto iter = this->iterate();
		auto pCurrent = iter.next();
		while (pCurrent)
		{
			if (match(pCurrent->value))
			{
				auto pRemoved = pCurrent;
				pCurrent = iter.next();
				this->remove(pRemoved);
				++count;
			}
			else
			{
				pCurrent = iter.next();
			}
		}

		return count;
	}

	bool remove(const ValueType &value)
	{
		auto iter = this->iterate();
		while (iter.has_next())
		{
			auto pNode = iter.next();
			if (pNode->value == value)
			{
				this->remove(pNode);
				return true;
			}
		}
		return false;
	}

	template <class LessThan>
	ListNode<ValueType>* insert(const ValueType &value, LessThan lt);

	void remove(ListNode<ValueType> *node);

	inline bool is_full() const;

private:

	ListNode<ValueType>* head_;
	ListNode<ValueType>* tail_;
	ListNode<ValueType>* free_;

	Array<ListNode<ValueType>, IndexType> underlying;

	ListNode<ValueType>* insert(const ValueType &value, ListNode<ValueType> *left, ListNode<ValueType> *right);

	inline static void link(ListNode<ValueType> *prev, ListNode<ValueType> *next);

	void initialize();
};

template <class ValueType, class IndexType>
ListNode<ValueType>* LinkedList<ValueType, IndexType>::add(const ValueType &value)
{
	return this->insert(value, tail_, nullptr);
}


template <class ValueType, class IndexType>
template <class LessThan>
ListNode<ValueType>* LinkedList<ValueType, IndexType>::insert(const ValueType &value, LessThan lt)
{
	if (free_ == nullptr)
	{
		return nullptr;
	}
	else
	{
		auto query = [lt, value](const ValueType & v)
		{
			return lt(value, v);
		};
		auto pResult = this->find_first(query);
		if (pResult)
		{
			return insert(value, pResult->prev_, pResult);
		}
		else
		{
			return insert(value, tail_, nullptr);
		}
	}
}

template <class ValueType, class IndexType>
ListNode<ValueType>* LinkedList<ValueType, IndexType>::insert(const ValueType &value, ListNode<ValueType> *pLeft,
															  ListNode<ValueType> *pRight)
{
	if (free_ == nullptr)
	{
		return nullptr;
	}
	else
	{
		// initialize the new node, and increment the length_
		auto pNode = free_;
		free_ = free_->next_;
		pNode->value = value;
		++(this->length_);

		this->link(pLeft, pNode);
		this->link(pNode, pRight);

		// change of head_
		if (pLeft == nullptr)
		{
			head_ = pNode;
		}

		// change of tail_
		if (pRight == nullptr)
		{
			tail_ = pNode;
		}

		return pNode;
	}
}

template <class ValueType, class IndexType>
template <class Selector>
ListNode<ValueType>* LinkedList<ValueType, IndexType>::find_first(Selector select)
{
	auto iter = this->iterate();
	while (iter.has_next())
	{
		auto pNode = iter.next();
		if (select(pNode->value))
		{
			return pNode;
		}
	}
	return nullptr;
}

template <class ValueType, class IndexType>
void LinkedList<ValueType, IndexType>::remove(ListNode<ValueType> *node)
{
	if(node->prev_ == nullptr) // it's the head_
	{
		if (node->next_ == nullptr)
		{
			head_ = tail_ = nullptr; // list is now empty_slice
		}
		else
		{
			head_ = node->next_; // head_ but not tail_
		}
	}
	else
	{
		if(node->next_ == nullptr) tail_ = node->prev_; // was only the tail_
	}

	// attach the adjacent nodes to eachother if they exist
	link(node->prev_, node->next_);

	// Now that the data list is complete, attach the freed node to the front of the free list
	node->next_ = free_;
	if(free_ != nullptr) free_->prev_ = node;
	node->prev_ = nullptr; // it's the head_ now
	free_ = node;
	--(this->length_);
}

template <class ValueType, class IndexType>
bool LinkedList<ValueType, IndexType>::is_full() const
{
	return (free_ == nullptr);
}



template <class ValueType, class IndexType>
void LinkedList<ValueType, IndexType>::link(ListNode<ValueType> *first, ListNode<ValueType> *second)
{
	if(first) first->next_ = second;
	if(second) second->prev_ = first;
}

template <class ValueType, class IndexType>
void LinkedList<ValueType, IndexType>::initialize()
{
	if(underlying.is_not_empty())
	{
		free_ = &underlying[0];
		for(IndexType i = 1; i < underlying.length(); ++i)
		{
			link(&underlying[i - 1], &underlying[i]);
		}
	}
}

}

#endif
