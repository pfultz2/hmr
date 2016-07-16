#include <hmr/iterator.hpp>
#include "test.hpp"

#include <vector>
#include <list>


PROVE_CASE()
{
    std::vector<int> x = {1,2,3,4,5,6,7,8,9};
    PROVE_CHECK(hmr::distance(x.begin(), x.end()) == 9);
}

PROVE_CASE()
{
    std::list<int> x = {1,2,3,4,5,6,7,8,9};
    PROVE_CHECK(hmr::distance(x.begin(), x.end()) == 9);
}
