#include <hmr/for_each.hpp>
#include "test.hpp"

PROVE_CASE()
{
    auto rng = hmr::view::yield(3);

    PROVE_CHECK(range_equal(rng, {3}));
    PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 1);
}


struct yield_if_is_odd
{
    auto operator()(int i) const FIT_RETURNS
    (
        hmr::view::yield_if((i % 2) == 1, i)
    );
};

struct yield_is_odd
{
    auto operator()(int i) const FIT_RETURNS
    (
        hmr::view::yield(bool{(i % 2) == 1})
    );
};

struct yield_squared
{
    auto operator()(int i) const FIT_RETURNS
    (
        hmr::view::yield(i*i)
    );
};

struct first
{
    template<class T>
    auto operator()(T x) const FIT_RETURNS
    (
        *hmr::begin(x)
    );
};

PROVE_CASE()
{
    std::vector<int> rgi = {1, 2, 3};
    auto rng = rgi | hmr::view::transform(yield_squared()) | hmr::view::transform(first());

    PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 3);    
}

PROVE_CASE()
{
    std::vector<int> rgi = {1, 2, 3};
    auto rngt = rgi | hmr::view::transform(yield_squared());
    auto rng = rngt | hmr::view::join;

    PROVE_CHECK(range_equal(rng, {1, 4, 9}));
    PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 3);    
}

PROVE_CASE()
{
    int rgi[] = {1, 2, 3};
    auto rng = rgi | hmr::view::transform(yield_squared()) | hmr::view::join;

    PROVE_CHECK(range_equal(rng, {1, 4, 9}));
    PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 3);    
}

PROVE_CASE()
{
    int rgi[] = {1, 2, 3};
    auto rng = hmr::view::for_each(rgi, yield_squared());

    PROVE_CHECK(range_equal(rng, {1, 4, 9}));
    PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 3);
}

PROVE_CASE()
{
    int rgi[] = {1};
    auto rng = hmr::view::for_each(rgi, yield_is_odd());

    PROVE_CHECK(range_equal(rng, {true}));
    PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 1);
}

PROVE_CASE()
{
    int rgi[] = {1, 2};
    auto rng = hmr::view::for_each(rgi, yield_is_odd());

    PROVE_CHECK(range_equal(rng, {true, false}));
    PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 2);
}

PROVE_CASE()
{
    int rgi[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto rng = hmr::view::for_each(rgi, yield_is_odd());

    PROVE_CHECK(range_equal(rng, {true, false, true, false, true, false, true, false, true, false}));
    PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 10);
}

PROVE_CASE()
{
    auto rng = hmr::view::yield_if(true, 3);

    PROVE_CHECK(range_equal(rng, {3}));
    PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 1);
}

PROVE_CASE()
{
    auto rng = hmr::view::yield_if(false, 3);

    PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 0);
}

PROVE_CASE()
{
    int rgi[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto rng = rgi | hmr::view::for_each(yield_if_is_odd());

    PROVE_CHECK(range_equal(rng, {1, 3, 5, 7, 9}));
}

