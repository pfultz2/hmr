/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    iterator_range.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HMR_GUARD_ITERATOR_RANGE_HPP
#define HMR_GUARD_ITERATOR_RANGE_HPP

#include <fit/construct.hpp>
#include <fit/function.hpp>

// To be removed
#include <fit/decay.hpp>
#include <fit/by.hpp>

namespace hmr {

template<class Iterator, class Sentinel>
struct iterator_range
{
    Iterator start;
    Sentinel last;

    iterator_range()
    {}

    iterator_range(Iterator s, Sentinel e) : start(s), last(e)
    {}

    Iterator begin() const
    {
        return start;
    }

    Sentinel end() const
    {
        return last;
    }
};

FIT_STATIC_FUNCTION(make_iterator_range) = fit::construct<iterator_range>().by(fit::decay);

} // namespace hmr

#endif
