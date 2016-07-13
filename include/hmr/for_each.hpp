/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    for_each.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HMR_GUARD_FOR_EACH_HPP
#define HMR_GUARD_FOR_EACH_HPP

#include <hmr/transform.hpp>
#include <hmr/join.hpp>
#include <hmr/iota.hpp>
#include <fit/compose.hpp>
#include <fit/partial.hpp>

namespace hmr {

namespace detail {

template<class T>
struct yield_range
{
    typedef typename std::remove_reference<T>::type value_type;
    typedef typename std::add_const<value_type>::type const_value_type;
    value_type data;

    yield_range() : data()
    {}

    yield_range(value_type x) : data(std::move(x))
    {}

    const_value_type* begin() const
    {
        return std::addressof(data);
    }

    const_value_type* end() const
    {
        return std::addressof(data)+1;
    }

    value_type* begin()
    {
        return std::addressof(data);
    }

    value_type* end()
    {
        return std::addressof(data)+1;
    }
};

template<class T>
struct yield_range<T&>
{
    T* data;
    typedef T value_type;
    typedef typename std::add_const<value_type>::type const_value_type;

    yield_range() : data(nullptr)
    {}

    yield_range(T& x) : data(std::addressof(x))
    {}

    const_value_type* begin() const
    {
        assert(data != nullptr);
        return data;
    }

    const_value_type* end() const
    {
        assert(data != nullptr);
        return data+1;
    }

    value_type* begin()
    {
        assert(data != nullptr);
        return data;
    }

    value_type* end()
    {
        assert(data != nullptr);
        return data+1;
    }
};

}

namespace view {

FIT_STATIC_FUNCTION(yield) = fit::construct<detail::yield_range>().by(fit::decay);
FIT_STATIC_FUNCTION(for_each) = fit::pipable(fit::limit_c<2>(fit::compose(make_adaptor_base<view::join_range>{}, make_adaptor_base<view::transform_range>{})));
}

namespace detail {

struct yield_if_fn
{
    template<class T>
    auto operator()(bool b, T&& x) const FIT_RETURNS
    (
        view::for_each(view::iota(b ? 1 : 0), fit::always(view::yield(std::forward<T>(x))))
    );
};

}

namespace view {

FIT_STATIC_FUNCTION(yield_if) = fit::partial(fit::limit_c<2>(detail::yield_if_fn{}));

}

} // namespace hmr

#endif
