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
#ifndef TESTLIB_TIMEOUT_H
#define TESTLIB_TIMEOUT_H

#include <chrono>

namespace openpal
{

// Use this class to simplify writing do loops with a timeout
// it minimizes the number of calls to get datetime and allows
// us to easily replace the implementation later if we find an
// even more effecient way to implement the timeout checking.
//
// Intended Usage:
//
// Timeout to(5000);
// do{
//	  //call some subordinate slow function
//	  bool success = WaitForInput(to.remaining());
//
//		//do something on success
//		if(success) return or break;
//
//		//or go back around the loop, the next_ call to
//		//remaining will be guarnteed to be > 0
// }while(!to.is_expired());
class Timeout
{
public:
	// constuctor, timeout will expire this many mills in the future
	Timeout(std::chrono::steady_clock::duration timeout);

	// returns whether its expired
	bool is_expired() const;

	// returns how much time is left
	std::chrono::steady_clock::duration remaining() const;


private:

	std::chrono::steady_clock::time_point expire_time_;

};


}

#endif