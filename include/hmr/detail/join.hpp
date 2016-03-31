/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    join.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HMR_GUARD_JOIN_HPP
#define HMR_GUARD_JOIN_HPP

namespace hmr { namespace detail {

template<class...>
struct alias_holder
{
    typedef void type;
};

template<template<class...> class Template, class T, class=void>
struct alias_join_impl;

template<template<class...> class Template, class... Ts>
struct alias_join_impl<Template, alias_holder<Ts...>, typename alias_holder<Template<Ts...>>::type>
{
    typedef Template<Ts...> type;
};

template<template<class...> class Template, class... Ts>
using alias_join = typename alias_join_impl<Template, alias_holder<Ts...>>::type;

}

} // namespace hmr

#endif
