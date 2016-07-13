/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    operators.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef HMR_GUARD_DETAIL_OPERATORS_HPP
#define HMR_GUARD_DETAIL_OPERATORS_HPP

#include <fit/returns.hpp>
#include <tick/requires.h>

namespace hmr { 

namespace detail {

template<class T>
struct arrow_proxy
{
    T x;
    arrow_proxy(T x_) : x(std::move(x_))
    {}
    const T* operator ->() const 
    {
        return &x;
    }
};

template<class T>
struct arrow_proxy<T&>
{
    T* x;
    arrow_proxy(T& x_) : x(&x_)
    {}
    T* operator ->() const 
    {
        return x;
    }
};

template<class T>
struct arrow_proxy_type
{ typedef arrow_proxy<T> type; };

template<class T>
struct arrow_proxy_type<T&&>
: arrow_proxy_type<T>
{};

template<class T>
typename arrow_proxy_type<T>::type make_arrow_proxy(T&& x)
{
    return {std::forward<T>(x)};
}

template<class T>
struct iterator_operators
{

    // Core operators

    // Increment
    template<class U, TICK_REQUIRES(std::is_same<U, T>::value)>
    friend auto operator++(U& x) FIT_RETURNS(U::increment(x));

    // Decrement
    template<class U, TICK_REQUIRES(std::is_same<U, T>::value)>
    friend auto operator--(U& x) FIT_RETURNS(U::decrement(x));

    // Advance
    template<class U, class I, TICK_REQUIRES(std::is_same<U, T>::value)>
    friend auto operator+=(U& x, I n) FIT_RETURNS(U::advance(x, n));

    // Distance
    template<class U, class Self=T>
    friend auto operator-(const T& x, const U& y) FIT_RETURNS(Self::distance(x, y));

    // Equal
    template<class U, class Self=T>
    friend auto operator==(const T& x, const U& y) FIT_RETURNS(Self::equal(x, y));

    template<class U>
    friend auto operator<(const T& x, const U& y) FIT_RETURNS(static_cast<bool>((x - y) < 0));
    template<class U>
    friend auto operator<=(const T& x, const U& y) FIT_RETURNS(!static_cast<bool>(x > y));
    template<class U>
    friend auto operator>=(const T& x, const U& y) FIT_RETURNS(!static_cast<bool>(x < y));
    template<class U>
    friend auto operator>(const T& x, const U& y) FIT_RETURNS(y < x);

    template<class U>
    friend auto operator!=(const T& x, const U& y) FIT_RETURNS(!static_cast<bool>(x == y));

    template<class U>
    friend auto operator +(T lhs, const U& rhs) -> decltype(T(lhs += rhs)) { return lhs += rhs; }
    template<class U, TICK_REQUIRES(!std::is_convertible<U, T>::value)>
    friend auto operator +(const U& lhs, T rhs) -> decltype(T(rhs += lhs)) { return rhs += lhs; }

    template<class U>
    friend auto operator-=(T& lhs, const U& rhs) FIT_RETURNS(lhs += -rhs);

    template<class U=T>
    friend auto operator++(U& x, int) -> decltype(T(++std::declval<U>()))
    {
        T nrv(x);
        ++x;
        return nrv;
    }

    template<class U=T>
    friend auto operator--(U& x, int) -> decltype(T(--std::declval<U>()))
    {
        T nrv(x);
        --x;
        return nrv;
    }

    template<class I, class U=T>
    auto operator[](I n) const FIT_RETURNS(*(static_cast<const U&>(*this) + n));

    template<class U=T>
    auto operator ->() const FIT_RETURNS(detail::make_arrow_proxy(*static_cast<const U&>(*this)));
};

}

} // namespace hmr

#endif
