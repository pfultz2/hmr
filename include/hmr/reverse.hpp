/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    reverse.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HMR_GUARD_REVERSE_HPP
#define HMR_GUARD_REVERSE_HPP

#include <hmr/detail/operators.hpp>
#include <hmr/detail/is_partial.hpp>
#include <hmr/adaptor_base.hpp>
#include <fit/function.hpp>
#include <fit/pipable.hpp>
#include <fit/limit.hpp>
#include <fit/apply.hpp>
#include <fit/construct.hpp>
#include <fit/construct.hpp>
#include <tick/requires.h>
#include <iterator>
#include <type_traits>
#include <cassert>

// To be removed
#include <fit/decay.hpp>
#include <fit/by.hpp>

namespace hmr {

namespace iterator {
template <class Iterator>
struct reverse_iterator : hmr::detail::iterator_operators<reverse_iterator<Iterator>>
{

    typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
    typedef typename std::iterator_traits<Iterator>::reference reference;
    typedef typename std::iterator_traits<Iterator>::value_type value_type;
    typedef typename std::iterator_traits<Iterator>::pointer pointer;
    typedef typename std::iterator_traits<Iterator>::iterator_category iterator_category;

    Iterator it;

    reverse_iterator()
    {}

    template<class T, FIT_ENABLE_IF_CONVERTIBLE(T, Iterator)>
    reverse_iterator(T i) : it(std::move(i))
    {}

    bool is_partial() const
    {
        return hmr::is_partial(it);
    }

    template<class T>
    static auto increment(T& x) FIT_RETURNS(--x.it);

    template<class T>
    static auto decrement(T& x) FIT_RETURNS(++x.it);

    template<class T, class I>
    static auto advance(T& x, I n) FIT_RETURNS(x.it += -n);

    template<class T>
    static auto distance(const T& x, const T& y) FIT_RETURNS(y.it - x.it);

    template<class T>
    static auto equal(const T& x, const T& y) FIT_RETURNS(x.it == y.it);

    reference operator *() const 
    {
        assert(!this->is_partial());
        Iterator r = it;
        --r;
        return *r;
    }    
};

FIT_STATIC_FUNCTION(make_reverse_iterator) = fit::construct<reverse_iterator>().by(fit::decay);

}

namespace detail {
struct reverse_base;
}

namespace view {

template<class R>
using reverse_range = adaptor_base<detail::reverse_base, R>;

FIT_STATIC_FUNCTION(reverse) = fit::pipable(fit::limit_c<1>(make_adaptor_base<reverse_range>{}));

}

namespace detail {

struct reverse_base
{
    reverse_base()
    {}

    template<class Range, class Self>
    static auto range_begin(Range&& r, Self&&) 
    FIT_RETURNS(iterator::make_reverse_iterator(hmr::end(r)));

    template<class Range, class Self>
    static auto range_end(Range&& r, Self&&) 
    FIT_RETURNS(iterator::make_reverse_iterator(hmr::begin(r)));
};

}

} // namespace hmr

#endif
