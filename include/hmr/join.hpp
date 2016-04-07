/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    join.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HMR_GUARD_JOIN_HPP
#define HMR_GUARD_JOIN_HPP

#include <hmr/detail/operators.hpp>
#include <hmr/adaptor_base.hpp>
#include <fit/function.hpp>
#include <fit/pipable.hpp>
#include <fit/limit.hpp>
#include <fit/apply.hpp>
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

std::input_iterator_tag join_iterator_tag(std::input_iterator_tag,std::input_iterator_tag);
std::forward_iterator_tag join_iterator_tag(std::forward_iterator_tag,std::forward_iterator_tag);
std::bidirectional_iterator_tag join_iterator_tag(std::bidirectional_iterator_tag,std::bidirectional_iterator_tag);

template<class OuterIterator, class OuterSentinel>
struct join_iterator : hmr::detail::iterator_operators<join_iterator<OuterIterator, OuterSentinel>>
{
    typedef decltype(*std::declval<OuterIterator>()) inner_range_reference;
    typedef decltype(hmr::begin(std::declval<inner_range_reference>())) inner_iterator;

    typedef typename std::iterator_traits<inner_iterator>::difference_type difference_type;
    typedef typename std::iterator_traits<inner_iterator>::reference reference;
    typedef typename std::iterator_traits<inner_iterator>::value_type value_type;
    typedef typename std::iterator_traits<inner_iterator>::pointer pointer;
    typedef decltype(
        iterator::join_iterator_tag(
            typename std::iterator_traits<OuterIterator>::iterator_category{}, 
            typename std::iterator_traits<inner_iterator>::iterator_category{}
        )
    ) iterator_category;

    OuterIterator iterator;
    OuterSentinel last;
    inner_iterator inner_it;

    join_iterator(OuterIterator iterator, OuterSentinel last) : iterator(iterator), last(last)
    {
        this->increment<std::false_type>();
    }

    bool is_outer_end() const
    {
        return this->iterator == this->last;
    }

    template<class Resume=std::true_type>
    void increment()
    {
        if (Resume{}) goto resume;
        for(;this->iterator!=this->last;++this->iterator)
        {
            assert(!this->is_outer_end());
            for(this->inner_it=hmr::begin(*this->iterator);this->inner_it!=hmr::end(*this->iterator);++this->inner_it)
            {
                return;
                resume:;
                assert(!this->is_outer_end());
            }
        }
    }

    template<class T>
    static T& increment(T& x)
    {
        x.increment();
        return x;
    }

    template<class T>
    static auto decrement(T& x) -> decltype((void)--x.iterator, (void)--x.inner_it, x)
    {
        if (x.iterator!=x.last) goto resume;
        for(;;)
        {
            --x.iterator;
            assert(!x.is_outer_end());
            for(x.inner_it=hmr::end(*x.iterator);x.inner_it!=hmr::begin(*x.iterator);)
            {
                --x.inner_it;
                return x;
                resume:;
                assert(!x.is_outer_end());
            }
        }
        return x;
    }

    template<class T>
    static bool equal(const T& x, const T& y)
    {
        x.iterator == y.iterator and (x.is_outer_end() or x.inner_it == y.inner_it);
    }

    reference operator *() const 
    {
        assert(!this->is_outer_end());
        assert(this->inner_it != hmr::end(*this->iterator));
        return *this->inner_it;
    } 

};

FIT_STATIC_FUNCTION(make_join_iterator) = fit::construct<join_iterator>().by(fit::decay);

}

namespace detail {
struct join_base;
}

namespace view {

template<class R>
using join_range = adaptor_base<detail::join_base, R>;

FIT_STATIC_FUNCTION(join) = fit::pipable(fit::limit_c<1>(make_adaptor_base<join_range>{}));

}

namespace detail {

struct join_base
{
    join_base()
    {}

    template<class Range, class Self>
    static auto range_begin(Range&& r, Self&&) 
    FIT_RETURNS(iterator::make_join_iterator(hmr::begin(r), hmr::end(r)));

    template<class Range, class Self>
    static auto range_end(Range&& r, Self&&) 
    FIT_RETURNS(iterator::make_join_iterator(hmr::end(r), hmr::end(r)));
};

}

} // namespace hmr

#endif
