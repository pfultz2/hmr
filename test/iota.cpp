#include <hmr/iota.hpp>
#include <hmr/reverse.hpp>
#include "test.hpp"

PROVE_CASE()
{
    auto rng = hmr::view::iota(10);
    PROVE_CHECK(range_equal(rng, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

PROVE_CASE()
{
    auto rng = hmr::view::iota(0, 10);
    PROVE_CHECK(range_equal(rng, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
}
