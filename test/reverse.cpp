#include <hmr/reverse.hpp>
#include <hmr/iterator.hpp>
#include "test.hpp"
#include <vector>
#include <list>

PROVE_CASE()
{
    std::vector<int> rgv{0,1,2,3,4,5,6,7,8,9};
    auto const rng = rgv | hmr::view::reverse;
    PROVE_CHECK(hmr::distance(rng.begin(), rng.end()));
    PROVE_CHECK(range_equal(rng, {9,8,7,6,5,4,3,2,1,0}));
    auto rrng = rng | hmr::view::reverse;
    PROVE_CHECK(range_equal(rrng, {0,1,2,3,4,5,6,7,8,9}));
    PROVE_CHECK(hmr::distance(rrng.begin(), rrng.end()));
    PROVE_CHECK(range_equal(rng | hmr::view::reverse, {0,1,2,3,4,5,6,7,8,9}));
}

PROVE_CASE()
{
    std::vector<int> rgv{0,1,2,3,4,5,6,7,8,9};
    PROVE_CHECK(range_equal(hmr::view::reverse(rgv), {9,8,7,6,5,4,3,2,1,0}));
    PROVE_CHECK(range_equal(hmr::view::reverse(hmr::view::reverse(rgv)), {0,1,2,3,4,5,6,7,8,9}));
    PROVE_CHECK(range_equal(hmr::view::reverse(rgv) | hmr::view::reverse, {0,1,2,3,4,5,6,7,8,9}));
}

PROVE_CASE()
{
    std::list<int> rgv{0,1,2,3,4,5,6,7,8,9};
    auto const rng = rgv | hmr::view::reverse;
    PROVE_CHECK(hmr::distance(rng.begin(), rng.end()));
    PROVE_CHECK(range_equal(rng, {9,8,7,6,5,4,3,2,1,0}));
    auto rrng = rng | hmr::view::reverse;
    PROVE_CHECK(range_equal(rrng, {0,1,2,3,4,5,6,7,8,9}));
    PROVE_CHECK(hmr::distance(rrng.begin(), rrng.end()));
    PROVE_CHECK(range_equal(rng | hmr::view::reverse, {0,1,2,3,4,5,6,7,8,9}));
}
