/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    ints.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HMR_GUARD_INTS_HPP
#define HMR_GUARD_INTS_HPP

#include <hmr/detail/iterator_iterator.hpp>
#include <hmr/iterator_range.hpp>
#include <fit/function.hpp>
#include <fit/pipable.hpp>
#include <fit/limit.hpp>

namespace hmr {

namespace detail {

struct ints_fn
{
    template<class T, class U>
    auto operator()(T start, U last) const FIT_RETURNS
    (
        hmr::make_iterator_range(
            hmr::iterator::iterator_iterator<T>(start), 
            hmr::iterator::iterator_iterator<T>(last)
        )
    );

    template<class T>
    auto operator()(T last) const FIT_RETURNS
    (
        hmr::make_iterator_range(
            hmr::iterator::iterator_iterator<T>(0), 
            hmr::iterator::iterator_iterator<T>(last)
        )
    )
};

}

namespace view {
FIT_STATIC_FUNCTION(ints) = fit::pipable(fit::limit_c<2>(detail::ints_fn()));

}

} // namespace hmr

#endif
