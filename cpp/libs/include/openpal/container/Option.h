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

        bool pop(T& output)
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

        void set(const T& value)
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

