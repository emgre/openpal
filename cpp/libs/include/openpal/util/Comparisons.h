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
#ifndef OPENPAL_COMPARISONS_H
#define OPENPAL_COMPARISONS_H

namespace openpal
{

template <class T>
inline T min(T a, T b)
{
	return (a < b) ? a : b;
}

template <class T>
inline T max(T a, T b)
{
	return (a > b) ? a : b;
}

template <class T>
inline T bounded(T value, T minimum, T maximum)
{
	return min(max(value, minimum), maximum);
}

template <class T>
inline bool is_within_limits(T value, T min, T max)
{
	return (value >= min) && (value <= max);
}

template <class T>
bool float_equal(T a, T b, T epsillon = 1e-6)
{
	T diff = a - b;
	if(diff < 0) diff = -diff;
	return diff <= epsillon;
}

}

#endif
