/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    join.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HMR_GUARD_JOIN_HPP
#define HMR_GUARD_JOIN_HPP

#include <hmr/detail/operators.hpp>
#include <hmr/detail/is_partial.hpp>
#include <hmr/adaptor_base.hpp>
#include <fit/function.hpp>
#include <fit/pipable.hpp>
#include <fit/limit.hpp>
#include <fit/apply.hpp>
#include <fit/construct.hpp>
#include <tick/requires.h>
#include <tick/traits/is_iterator.h>
#include <iterator>
#include <type_traits>
#include <cassert>

// To be removed
#include <fit/decay.hpp>
#include <fit/by.hpp>

namespace hmr {

namespace iterator {

namespace detail {

std::input_iterator_tag join_iterator_tag(std::input_iterator_tag,std::input_iterator_tag);
std::forward_iterator_tag join_iterator_tag(std::forward_iterator_tag,std::forward_iterator_tag);
std::bidirectional_iterator_tag join_iterator_tag(std::bidirectional_iterator_tag,std::bidirectional_iterator_tag);

template<class T, class=void>
struct inner_range
{
    typedef decltype(hmr::begin(std::declval<T>())) inner_iterator;
    T data;
    inner_iterator iterator;

    static_assert(std::is_default_constructible<T>{}, "Not valid inner range");

    inner_range() : data(), iterator()
    {}

    inner_range(inner_iterator it) : iterator(it)
    {}

    bool is_partial() const
    {
        return hmr::is_partial(data) and hmr::is_partial(iterator);
    }

    template<class U>
    void set(U&& x)
    {
        data = std::forward<U>(x);
    }

    inner_iterator begin()
    {
        return hmr::begin(data);
    }

    inner_iterator end() 
    {
        return hmr::end(data);
    }

    bool is_end() const
    {
        return hmr::end(data) == iterator;
    }
};

template<class T>
struct inner_range<T&>
{
    typedef decltype(hmr::begin(std::declval<T&>())) inner_iterator;
    T* data;
    inner_iterator iterator;

    inner_range() : data(), iterator()
    {}

    inner_range(inner_iterator it) : iterator(it)
    {}

    bool is_partial() const
    {
        return data != nullptr and hmr::is_partial(iterator);
    }

    void set(T& x)
    {
        data = &x;
    }

    inner_iterator begin()
    {
        assert(data != nullptr);
        return hmr::begin(*data);
    }

    inner_iterator end() 
    {
        assert(data != nullptr);
        return hmr::end(*data);
    }

    bool is_end() const
    {
        assert(data != nullptr);
        return hmr::end(*data) == iterator;
    }
};

}

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
        detail::join_iterator_tag(
            typename std::iterator_traits<OuterIterator>::iterator_category{}, 
            typename std::iterator_traits<inner_iterator>::iterator_category{}
        )
    ) iterator_category;


    OuterIterator iterator;
    OuterSentinel last;
    detail::inner_range<inner_range_reference> inner;

    join_iterator()
    {}

    join_iterator(OuterIterator iterator_, OuterSentinel last_) : iterator(iterator_), last(last_)
    {
        this->increment<std::false_type>();
        assert(this->check());
    }

    bool is_partial() const
    {
        return hmr::is_partial(this->iterator) and this->inner.is_partial();
    }

    bool is_outer_end() const
    {
        return this->iterator == this->last;
    }

    template< class Other >
    bool is_compatible(const Other& other) const
    {
        return last == other.last;
    }

    bool check() const
    {
        return this->is_outer_end() or !this->inner.is_end();
    }

    template<class Resume=std::true_type>
    void increment()
    {
        if (Resume{}) goto resume;
        for(;this->iterator!=this->last;++this->iterator)
        {
            assert(!this->is_outer_end());
            this->inner.set(*this->iterator);
            for(this->inner.iterator=this->inner.begin();this->inner.iterator!=this->inner.end();++this->inner.iterator)
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
        assert(!x.is_partial() and !x.is_outer_end() and !x.inner.is_end());
        x.increment();
        assert(x.check());
        return x;
    }

    template<class T>
    static auto decrement(T& x) -> decltype((void)--x.iterator, (void)--x.inner.iterator, x)
    {
        if (x.iterator!=x.last) goto resume;
        for(;;)
        {
            --x.iterator;
            assert(!x.is_outer_end());
            x.inner.set(*x.iterator);
            for(x.inner.iterator=x.inner.end();x.inner.iterator!=x.inner.begin();)
            {
                --x.inner.iterator;
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
        assert(!x.is_partial() and !y.is_partial() and x.is_compatible(y));
        return x.iterator == y.iterator and (x.is_outer_end() or y.is_outer_end() or x.inner.iterator == y.inner.iterator);
    }

    reference operator *() const 
    {
        assert(!this->is_partial() and !this->is_outer_end() and !this->inner.is_end());
        return *this->inner.iterator;
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
    static auto segments(Range&& r, Self&&)
    FIT_RETURNS(r);

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
