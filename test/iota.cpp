#include <hmr/iota.hpp>
#include <hmr/reverse.hpp>
#include <hmr/iterator.hpp>
#include "test.hpp"

PROVE_CASE()
{
    auto rng = hmr::view::iota(10);
    PROVE_CHECK(range_equal(rng, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
    PROVE_CHECK(hmr::distance(rng.begin(), rng.end()) == 10);
}

PROVE_CASE()
{
    auto rng = hmr::view::iota(0, 10);
    PROVE_CHECK(range_equal(rng, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
    PROVE_CHECK(hmr::distance(rng.begin(), rng.end()) == 10);
}

PROVE_CASE()
{
    auto rng = hmr::view::iota(0);
    PROVE_CHECK(bool(rng.begin() == rng.end()));
    PROVE_CHECK(hmr::distance(rng.begin(), rng.end()) == 0);
}

PROVE_CASE()
{
    auto rng = hmr::view::iota(0, 0);
    PROVE_CHECK(bool(rng.begin() == rng.end()));
    PROVE_CHECK(hmr::distance(rng.begin(), rng.end()) == 0);
}

PROVE_CASE()
{
    auto rng = hmr::view::iota(1);
    PROVE_CHECK(range_equal(rng, {0}));
    PROVE_CHECK(hmr::distance(rng.begin(), rng.end()) == 1);
}

PROVE_CASE()
{
    auto rng = hmr::view::iota(1, 2);
    PROVE_CHECK(range_equal(rng, {1}));
    PROVE_CHECK(hmr::distance(rng.begin(), rng.end()) == 1);
}
