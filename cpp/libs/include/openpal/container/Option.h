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
#ifndef OPENPAL_OPTION_H
#define OPENPAL_OPTION_H

namespace openpal
{

// utility class for representing a value that may or may not be set
template <class T>
class Option
{
public:

	Option() : value_is_set_(false)
	{}

	bool IsSet() const
	{
		return value_is_set_;
	}

	bool IsEmpty() const
	{
		return !value_is_set_;
	}

	T Get() const
	{
		return value_;
	}

	bool pop(T &output)
	{
		if (value_is_set_)
		{
			value_is_set_ = false;
			output = value_;
			return true;
		}
		else
		{
			return false;
		}
	}

	void clear()
	{
		value_is_set_ = false;
	}

	void set(const T &value)
	{
		value_ = value;
		value_is_set_ = true;
	}

	template <class Action>
	bool is_set_and(Action action);

	template <class Action>
	void foreach(Action action);


private:

	bool value_is_set_;
	T value_;
};

template <class T>
template <class Action>
bool Option<T>::is_set_and(Action action)
{
	if (value_is_set_)
	{
		return action(value_);
	}
	else
	{
		return false;
	}
}

template <class T>
template <class Action>
void Option<T>::foreach(Action action)
{
	if (value_is_set_)
	{
		action(value_);
	}
}

}


#endif

