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
#ifndef OPENPAL_RSEQ_H
#define OPENPAL_RSEQ_H

#include "HasLength.h"

#include "openpal/util/Comparisons.h"

#include <limits>
#include <cstdint>

namespace openpal
{    

    /**
    *	Represents a readonly slice of bytes with a parameterized length type (L)
    */
	template <class L>
    class RSeq : public HasLength<L>
    {
		static_assert(std::numeric_limits<L>::is_integer && !std::numeric_limits<L>::is_signed, "Must be an unsigned integer");

    public:       

		static RSeq empty_slice()
		{
			return RSeq(nullptr, 0);
		}

		RSeq() : HasLength(0), buffer_(nullptr)
		{}

		RSeq(uint8_t const* buffer, L length) :
			HasLength(length),
			buffer_(buffer)
		{}

        void make_empty()
		{
			buffer_ = nullptr;
			length_ = 0;
		}

		template <class U>
		RSeq<U> widen() const
		{
			return RSeq<U>(buffer_, length_);
		}

		template <class U>
		RSeq<U> take(U count) const
		{
			return RSeq<U>(this->buffer_, (count < this->length_) ? count : static_cast<U>(this->length_));
		}

		RSeq skip(L count) const
		{
			auto num = openpal::min(length_, count);
			return RSeq(buffer_ + num, length_ - num);
		}

        void advance(L count)
		{
			auto num = openpal::min(length_, count);
			buffer_ += num;
			length_ -= num;
		}

		operator uint8_t const* () const
		{
			return buffer_;
		};

		bool equals(const RSeq& rhs) const
		{
			if (this->length() == rhs.length())
			{
				return memcmp(buffer_, rhs.buffer_, length()) == 0;
			}
			else
			{
				return false;
			}
		}

	protected:

		uint8_t const* buffer_;

    };

}

#endif
