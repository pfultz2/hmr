/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    iota.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HMR_GUARD_IOTA_HPP
#define HMR_GUARD_IOTA_HPP

#include <hmr/detail/operators.hpp>
#include <hmr/adaptor_base.hpp>
#include <fit/function.hpp>
#include <fit/pipable.hpp>
#include <fit/limit.hpp>
#include <fit/apply.hpp>
#include <tick/requires.h>
#include <iterator>
#include <type_traits>
#include <cassert>
#include <hmr/iterator_range.hpp>

namespace hmr {

namespace iterator {
template <class Iterator>
struct iota_iterator : hmr::detail::iterator_operators<iota_iterator<Iterator>>
{
    Iterator it;

    typedef decltype(it-it) difference_type;
    typedef Iterator reference;
    typedef Iterator value_type;
    typedef value_type* pointer;
    typedef std::input_iterator_tag iterator_category;

    iota_iterator() : it()
    {}

    template<class T, FIT_ENABLE_IF_CONVERTIBLE(T, Iterator)>
    iota_iterator(T i) : it(std::move(i))
    {}

    template<class T>
    static auto increment(T& x) FIT_RETURNS(++x.it);

    template<class T>
    static auto decrement(T& x) FIT_RETURNS(--x.it);

    template<class T, class I>
    static auto advance(T& x, I n) FIT_RETURNS(x.it += n);

    template<class T, class U>
    static auto distance(const T& x, const U& y) FIT_RETURNS(y.it - x.it);

    template<class T, class U>
    static auto equal(const T& x, const U& y) FIT_RETURNS(x.it == y.it);

    reference operator *() const 
    {
        return it;
    }    
};

template<class T>
iota_iterator<T> make_iota_iterator(T it)
{
    return {std::move(it)};
}

}

namespace detail {

struct iota_fn
{
    template<class T, class U>
    auto operator()(T start, U last) const FIT_RETURNS
    (
        hmr::make_iterator_range(
            hmr::iterator::iota_iterator<T>(start), 
            hmr::iterator::iota_iterator<T>(last)
        )
    );

    template<class T>
    auto operator()(T last) const FIT_RETURNS
    (
        hmr::make_iterator_range(
            hmr::iterator::iota_iterator<T>(0), 
            hmr::iterator::iota_iterator<T>(last)
        )
    )
};

}

namespace view {
FIT_STATIC_FUNCTION(iota) = fit::pipable(fit::limit_c<2>(detail::iota_fn()));

}

} // namespace hmr

#endif
