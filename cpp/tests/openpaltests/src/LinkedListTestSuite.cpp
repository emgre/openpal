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
#include <catch.hpp>

#include <openpal/container/Array.h>
#include <openpal/container/LinkedList.h>

using namespace openpal;

#define SUITE(name) "LinkedListAdapter - " name

TEST_CASE(SUITE("CorrectInitialState"))
{
	LinkedList<int, uint16_t> list(3);

	REQUIRE(list.is_empty());
	REQUIRE(!list.is_full());
	REQUIRE(0 == list.length());
}

TEST_CASE(SUITE("AddsUntilFull"))
{
	LinkedList<int, uint16_t> list(3);

	REQUIRE(list.add(1));
	REQUIRE(list.add(2));
	REQUIRE(list.add(3));

	REQUIRE(list.is_full());

	// adding to a full list returns a nullptr
	REQUIRE_FALSE(list.add(4));
}

TEST_CASE(SUITE("CanRemoveHead"))
{
	LinkedList<int, uint16_t> list(3);

	auto one = list.add(1);
	list.add(2);
	list.add(3);

	list.remove(one);

	REQUIRE(2 == list.length());

	auto four = list.add(4);

	REQUIRE(four == one); // these pointers should be the same
}

TEST_CASE(SUITE("CanRemoveTail"))
{
	LinkedList<int, uint16_t> list(3);

	list.add(1);
	list.add(2);
	auto three = list.add(3);

	list.remove(three);

	REQUIRE(2 == list.length());

	auto four = list.add(4);

	REQUIRE(four == three); // these pointers should be the same
}

TEST_CASE(SUITE("CanRemoveMiddle"))
{
	LinkedList<int, uint16_t> list(3);

	list.add(1);
	auto two = list.add(2);
	list.add(3);

	list.remove(two);

	REQUIRE(2 == list.length());

	auto four = list.add(4);

	REQUIRE(four == two); // these pointers should be the same
}

TEST_CASE(SUITE("RemoveAllComplexQuery"))
{
	LinkedList<int, uint16_t> list(10);

	list.add(2);
	list.add(3);
	list.add(4);
	list.add(7);
	list.add(20);
	list.add(8);

	auto isEven = [](int num)
	{
		return (num % 2) == 0;
	};
	auto count = list.remove_all(isEven);

	REQUIRE(count == 4);
	REQUIRE(list.length() == 2);

	std::vector<int> remaining;
	auto pushToVector = [&](int num)
	{
		remaining.push_back(num);
	};
	list.foreach(pushToVector);

	REQUIRE(remaining.size() == 2);
	REQUIRE(remaining[0] == 3);
	REQUIRE(remaining[1] == 7);
}

TEST_CASE(SUITE("CanIterateOverValues"))
{
	LinkedList<int, uint16_t> list(3);

	list.add(1);
	list.add(2);
	list.add(3);

	auto iter = list.iterate();

	for(int i = 1; i < 4; ++i)
	{
		REQUIRE(iter.has_next());
		REQUIRE(i == iter.next()->value);
	}

	REQUIRE(!iter.has_next());
}

TEST_CASE(SUITE("StaticLinkedList"))
{
	LinkedList<int, uint16_t> list(3);

	REQUIRE(list.add(1));
	REQUIRE(list.add(2));
	REQUIRE(list.add(3));
	REQUIRE_FALSE(list.add(4));

	REQUIRE(list.remove(2));
}

TEST_CASE(SUITE("insert at front of list"))
{
	LinkedList<int, uint16_t> list(3);

	REQUIRE(list.add(7));

	auto lessThan = [](int lhs, int rhs)
	{
		return lhs < rhs;
	};
	REQUIRE(list.insert(4, lessThan));

	std::vector<int> items;

	list.foreach([&](int x) {
		items.push_back(x);
	});
	REQUIRE(items.size() == 2);
	REQUIRE(items[0] == 4);
	REQUIRE(items[1] == 7);
}

TEST_CASE(SUITE("insert in center of list"))
{
	LinkedList<int, uint16_t> list(10);

	REQUIRE(list.add(2));
	REQUIRE(list.add(7));

	auto lessThan = [](int lhs, int rhs)
	{
		return lhs < rhs;
	};
	REQUIRE(list.insert(4, lessThan));

	std::vector<int> items;

	list.foreach([&](int x) {
		items.push_back(x);
	});
	REQUIRE(items.size() == 3);

	REQUIRE(items[0] == 2);
	REQUIRE(items[1] == 4);
	REQUIRE(items[2] == 7);
}

TEST_CASE(SUITE("insert at end of list"))
{
	LinkedList<int, uint16_t> list(10);

	REQUIRE(list.add(2));
	REQUIRE(list.add(4));

	auto lessThan = [](int lhs, int rhs)
	{
		return lhs < rhs;
	};
	REQUIRE(list.insert(7, lessThan));

	std::vector<int> items;

	list.foreach([&](int x) {
		items.push_back(x);
	});
	REQUIRE(items.size() == 3);

	REQUIRE(items[0] == 2);
	REQUIRE(items[1] == 4);
	REQUIRE(items[2] == 7);
}

