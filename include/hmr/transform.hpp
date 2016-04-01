/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    transform.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HMR_GUARD_TRANSFORM_HPP
#define HMR_GUARD_TRANSFORM_HPP

#include <hmr/detail/operators.hpp>
#include <hmr/adaptor_base.hpp>
#include <fit/function.hpp>
#include <fit/pipable.hpp>
#include <fit/limit.hpp>
#include <fit/apply.hpp>
#include <tick/requires.h>
#include <iterator>
#include <type_traits>


namespace hmr {

namespace iterator {
template <class Iterator, class Range>
struct transform_iterator : hmr::detail::iterator_operators<transform_iterator<Iterator, Range>>
{

    typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
    typedef decltype(fit::apply(std::declval<Range>().f,*std::declval<Iterator>())) reference;
    typedef typename std::decay<reference>::type value_type;
    typedef value_type* pointer;
    typedef typename std::conditional<
        (std::is_reference<reference>::value), 
        typename std::iterator_traits<Iterator>::iterator_category, 
        std::input_iterator_tag
    >::type iterator_category;

    Iterator it;
    Range* rng;

    transform_iterator()
    {}

    template<class T, FIT_ENABLE_IF_CONVERTIBLE(T, Iterator)>
    transform_iterator(T i, Range& r) : it(std::move(i)), rng(&r)
    {}

    template<class T>
    static auto increment(T& x) FIT_RETURNS(++x.it);

    template<class T>
    static auto decrement(T& x) FIT_RETURNS(--x.it);

    template<class T, class I>
    static auto advance(T& x, I n) FIT_RETURNS(x.it += n);

    template<class T>
    static auto distance(const T& x, const T& y) FIT_RETURNS(x.it - y.it);

    template<class T>
    static auto equal(const T& x, const T& y) FIT_RETURNS(x.it == y.it);

    reference operator *() const 
    {
        return fit::apply(rng->f, *it);
    }    
};

}
namespace detail {
template<class F>
struct transform_base;
}

namespace view {

template<class R, class F>
using transform_range = adaptor_base<detail::transform_base<F>, R>;

FIT_STATIC_FUNCTION(transform) = fit::pipable(fit::limit_c<2>(make_adaptor_base<transform_range>{}));

}

namespace detail {

template<class F>
struct transform_base
{
    F f;
    transform_base(F f) : f(std::move(f))
    {}

    template<class Iterator, class Self>
    static iterator::transform_iterator<Iterator, Self> iterator_create(Iterator it, Self& self)
    {
        return {it, self};
    }
};

}


} // namespace hmr

#endif
