/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    iterator.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HMR_GUARD_ITERATOR_HPP
#define HMR_GUARD_ITERATOR_HPP

#include <hmr/beginend.hpp>
#include <fit/conditional.hpp>
#include <fit/function.hpp>

namespace hmr {

namespace detail {

struct distance_subtract_fn
{
    template<class Sentinel, class Iterator>
    auto operator()(Sentinel s, Iterator i) const FIT_RETURNS
    (s - i);
};

struct distance_calc_fn
{
    template<class Sentinel, class Iterator>
    typename std::iterator_traits<Iterator>::difference_type 
    operator()(Sentinel s, Iterator i) const
    {
        typename std::iterator_traits<Iterator>::difference_type r = 0;
        while(i != s)
        {
            ++i;
            ++r;
        }
        return r;
    }
};

struct advance_advanceable_fn
{
    template<class Iterator, class Numeric>
    auto operator()(Iterator& it, Numeric n) const 
    FIT_RETURNS(it += n);
};

struct advance_decrementable_fn
{
    template<class Iterator, class Numeric>
    auto operator()(Iterator& it, Numeric n) const -> decltype((void)++it, (void)--it)
    {
        if (n > 0) while (n--) ++it;
        else 
        {
            n = -n;
            while (n--) --it;
        }
    }
};

struct advance_incrementable_fn
{
    template<class Iterator, class Numeric>
    void operator()(Iterator& it, Numeric n) const
    {
        assert(n > 0);
        while (n--) ++it;
    }
};

}

FIT_STATIC_FUNCTION(distance) = fit::conditional(
    detail::distance_subtract_fn{},
    detail::distance_calc_fn{}
);

FIT_STATIC_FUNCTION(advance) = fit::conditional(
    detail::advance_advanceable_fn{},
    detail::advance_decrementable_fn{},
    detail::advance_incrementable_fn{}
);

namespace detail {

struct next_fn
{
    template<class Iterator, class Numeric>
    Iterator operator()(Iterator i, Numeric n) const
    {
        hmr::advance(i, n);
        return i;
    }
};

}

FIT_STATIC_FUNCTION(next) = detail::next_fn{};

} // namespace hmr

#endif
