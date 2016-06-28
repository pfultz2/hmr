/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    is_partial.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HMR_GUARD_IS_PARTIAL_HPP
#define HMR_GUARD_IS_PARTIAL_HPP

#include <fit/conditional.hpp>
#include <fit/function.hpp>

namespace hmr { namespace detail {

struct is_partial_pointer
{
    template<class T>
    bool operator()(T* x) const
    {
        return x == nullptr;
    }
};

struct is_partial_object
{
    template<class T>
    auto operator()(T&& x) const 
    FIT_RETURNS(x.is_partial());
};

}

FIT_STATIC_FUNCTION(is_partial) = fit::conditional(
    detail::is_partial_pointer{},
    detail::is_partial_object{},
    fit::always(std::false_type{})
);

} // namespace hmr

#endif
