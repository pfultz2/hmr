/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    beginend.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HMR_GUARD_BEGINEND_HPP
#define HMR_GUARD_BEGINEND_HPP

#include <iterator>
#include <fit/function.hpp>
#include <fit/returns.hpp>

namespace hmr_adl {

using std::begin;
using std::end;

struct adl_begin
{
    template<class T>
    constexpr auto operator()(T&& x) const FIT_RETURNS(begin(std::forward<T>(x)));
};

struct adl_end
{
    template<class T>
    constexpr auto operator()(T&& x) const FIT_RETURNS(end(std::forward<T>(x)));
};

}


namespace hmr {

FIT_STATIC_FUNCTION(begin) = hmr_adl::adl_begin{};
FIT_STATIC_FUNCTION(end) = hmr_adl::adl_end{};

} // namespace hmr

#endif
