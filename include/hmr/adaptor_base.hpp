/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    adaptor_base.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HMR_GUARD_ADAPTOR_BASE_HPP
#define HMR_GUARD_ADAPTOR_BASE_HPP

#include <fit/detail/delegate.hpp>
#include <hmr/detail/is_partial.hpp>
#include <fit/returns.hpp>
#include <hmr/beginend.hpp>
#include <hmr/detail/join.hpp>
#include <cassert>

namespace hmr { namespace detail {

template<class Range>
class adaptor_base_storage
{
    Range rng_;
public:
    
    template<class... Ts>
    adaptor_base_storage(Ts&&... xs) : rng_(std::forward<Ts>(xs)...)
    {}

    Range &base_range()
    {
        return rng_;
    }
    Range const &base_range() const
    {
        return rng_;
    }

    auto base_begin() FIT_RETURNS(hmr::begin(this->base_range()));

    auto base_end() FIT_RETURNS(hmr::end(this->base_range()));

    auto base_begin() const FIT_RETURNS(hmr::begin(this->base_range()));

    auto base_end() const FIT_RETURNS(hmr::end(this->base_range()));
};

template<class Range>
class adaptor_base_storage<Range &>
{
    Range *rng_;
public:
    adaptor_base_storage()
    {}

    adaptor_base_storage(Range& r) : rng_(&r)
    {}
    Range &base_range()
    {
        assert(rng_ != nullptr);
        return *rng_;
    }

    const Range &base_range() const
    {
        assert(rng_ != nullptr);
        return *rng_;
    }

    auto base_begin() FIT_RETURNS(hmr::begin(this->base_range()));

    auto base_end() FIT_RETURNS(hmr::end(this->base_range()));

    auto base_begin() const FIT_RETURNS(hmr::begin(this->base_range()));

    auto base_end() const FIT_RETURNS(hmr::end(this->base_range()));
};

}

template<class Adaptor, class Range>
struct adaptor_base : Adaptor, detail::adaptor_base_storage<Range>
{
    typedef detail::adaptor_base_storage<Range> range_base;
    template<class R, class... Ts, class=typename std::enable_if<(
        std::is_convertible<R, range_base>::value && 
        std::is_constructible<Adaptor, Ts&&...>::value
    )>::type>
    adaptor_base(R&& r, Ts&&... xs) : Adaptor(std::forward<Ts>(xs)...), range_base(std::forward<R>(r))
    {}

    Adaptor& base_adaptor()
    {
        return *this;
    }

    const Adaptor& base_adaptor() const
    {
        return *this;
    }

    bool is_partial() const
    {
        return hmr::is_partial(this->base_adaptor()) and hmr::is_partial(this->base_range());
    }

    template<class T=Adaptor, int=0>
    auto segments() FIT_RETURNS(T::segments(this->base_range(), this->base_adaptor()));

    template<class T=Adaptor, long=0>
    auto segments() const FIT_RETURNS(T::segments(this->base_range(), this->base_adaptor()));

    template<class T=Adaptor, int=0>
    auto begin() FIT_RETURNS(T::range_begin(this->base_range(), this->base_adaptor()));

    template<class T=Adaptor, int=0>
    auto end() FIT_RETURNS(T::range_end(this->base_range(), this->base_adaptor()));

    template<class T=Adaptor, int=0>
    auto begin() const FIT_RETURNS(T::range_begin(this->base_range(), this->base_adaptor()));

    template<class T=Adaptor, int=0>
    auto end() const FIT_RETURNS(T::range_end(this->base_range(), this->base_adaptor()));

    template<class T=Adaptor, long=0>
    auto begin() FIT_RETURNS(T::iterator_create(this->base_begin(), this->base_adaptor()));

    template<class T=Adaptor, long=0>
    auto end() FIT_RETURNS(T::iterator_create(this->base_end(), this->base_adaptor()));

    template<class T=Adaptor, long=0>
    auto begin() const FIT_RETURNS(T::iterator_create(this->base_begin(), this->base_adaptor()));

    template<class T=Adaptor, long=0>
    auto end() const FIT_RETURNS(T::iterator_create(this->base_end(), this->base_adaptor()));
};



template<template<class...> class Adaptor>
struct make_adaptor_base
{
    constexpr make_adaptor_base()
    {}

    template<class Range, class... Ts,
        class Result=detail::alias_join<Adaptor, Range, Ts...>
    >
    constexpr Result operator()(Range&& r, Ts... xs) const
    {
        return Result(static_cast<Range&&>(r), static_cast<Ts&&>(xs)...);
    }
};

} // namespace hmr

#endif
