#include <hmr/join.hpp>
#include "test.hpp"

PROVE_CASE()
{
    std::vector<std::string> vs{"hello","world","!"};
    auto s = vs | hmr::view::join;
    PROVE_CHECK(to_<std::string>(s) == "helloworld!");
}
