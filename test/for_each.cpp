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


PROVE_CASE()
{
    int rgi[] = {1, 2, 3};
    auto rng = rgi | hmr::view::transform(yield_squared());

    PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 3);    
}

PROVE_CASE()
{
    int rgi[] = {1, 2, 3};
    auto rng = rgi | hmr::view::transform(yield_squared()) | hmr::view::join;

    auto segs = rng.segments();
    PROVE_CHECK(std::distance(segs.begin(), segs.end()) == 3);

    PROVE_CHECK(range_equal(rng, {1, 4, 9}));
    PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 3);    
}

// PROVE_CASE()
// {
//     int rgi[] = {1, 2, 3};
//     auto rng = hmr::view::for_each(rgi, yield_squared());

//     PROVE_CHECK(range_equal(rng, {1, 4, 9}));
//     PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 3);
// }

// PROVE_CASE()
// {
//     int rgi[] = {1};
//     auto rng = hmr::view::for_each(rgi, yield_is_odd());

//     PROVE_CHECK(range_equal(rng, {true}));
//     PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 1);
// }

// PROVE_CASE()
// {
//     int rgi[] = {1, 2};
//     auto rng = hmr::view::for_each(rgi, yield_is_odd());

//     PROVE_CHECK(range_equal(rng, {true, false}));
//     PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 2);
// }

// PROVE_CASE()
// {
//     int rgi[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     auto rng = hmr::view::for_each(rgi, yield_is_odd());

//     PROVE_CHECK(range_equal(rng, {true, false, true, false, true, false, true, false, true, false}));
//     PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 10);
// }

// PROVE_CASE()
// {
//     auto rng = hmr::view::yield_if(true, 3);

//     PROVE_CHECK(range_equal(rng, {3}));
//     PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 1);
// }

// PROVE_CASE()
// {
//     auto rng = hmr::view::yield_if(false, 3);

//     PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 0);
// }

// PROVE_CASE()
// {
//     int rgi[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     auto rng = rgi | hmr::view::for_each(yield_if_is_odd());

//     PROVE_CHECK(range_equal(rng, {1, 3, 5, 7, 9}));
// }

