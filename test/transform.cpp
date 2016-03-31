#include <hmr/transform.hpp>
#include "test.hpp"

struct is_odd
{
    bool operator()(int i) const
    {
        return (i % 2) == 1;
    }
};

PROVE_CASE()
{
    int rgi[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto rng = rgi | hmr::view::transform(is_odd());

    PROVE_CHECK(range_equal(rng, {true, false, true, false, true, false, true, false, true, false}));
    PROVE_CHECK((rng.end() - rng.begin()) == 10);
    PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 10);
}


PROVE_CASE()
{
    int rgi[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto rng = hmr::view::transform(rgi, is_odd());

    PROVE_CHECK(range_equal(rng, {true, false, true, false, true, false, true, false, true, false}));
    PROVE_CHECK((rng.end() - rng.begin()) == 10);
    PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 10);
}

PROVE_CASE()
{
    std::pair<int, int> rgp[] = {{1,1}, {2,2}, {3,3}, {4,4}, {5,5}, {6,6}, {7,7}, {8,8}, {9,9}, {10,10}};
    auto rng = rgp | hmr::view::transform(&std::pair<int,int>::first);
    PROVE_CHECK(range_equal(rng, {1,2,3,4,5,6,7,8,9,10}));
    PROVE_CHECK((rng.end() - rng.begin()) == 10);
    PROVE_CHECK(std::distance(rng.begin(), rng.end()) == 10);
    PROVE_CHECK(&*begin(rng) == &rgp[0].first);
}
