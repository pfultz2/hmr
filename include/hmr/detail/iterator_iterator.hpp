/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    iterator_iterator.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HMR_GUARD_ITERATOR_ITERATOR_HPP
#define HMR_GUARD_ITERATOR_ITERATOR_HPP

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

template <class Iterator>
struct iterator_iterator : hmr::detail::iterator_operators<iterator_iterator<Iterator>>
{
    Iterator it;

    typedef decltype(it-it) difference_type;
    typedef Iterator reference;
    typedef Iterator value_type;
    typedef value_type* pointer;
    typedef std::input_iterator_tag iterator_category;

    iterator_iterator()
    {}

    template<class T, FIT_ENABLE_IF_CONVERTIBLE(T, Iterator)>
    iterator_iterator(T i) : it(std::move(i))
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
        return it;
    }    
};

template<class T>
iterator_iterator<T> make_iterator_iterator(T it)
{
    return {std::move(it)};
}

}

} // namespace hmr

#endif
