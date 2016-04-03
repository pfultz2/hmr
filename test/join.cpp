#include <hmr/join.hpp>
#include "test.hpp"

PROVE_CASE()
{
    std::vector<std::string> vs{"hello","world","!"};
    auto s = vs | hmr::view::join;
    PROVE_CHECK(to_<std::string>(s) == "helloworld!");
}

PROVE_CASE()
{
    std::vector<std::string> vs{"hello","","world","","!"};
    auto s = vs | hmr::view::join;
    PROVE_CHECK(to_<std::string>(s) == "helloworld!");
}

PROVE_CASE()
{
    std::vector<std::string> vs{"", "hello","world","!"};
    auto s = vs | hmr::view::join;
    PROVE_CHECK(to_<std::string>(s) == "helloworld!");
}

PROVE_CASE()
{
    std::vector<std::string> vs{"hello","world","!", ""};
    auto s = vs | hmr::view::join;
    PROVE_CHECK(to_<std::string>(s) == "helloworld!");
}

PROVE_CASE()
{
    std::vector<std::string> vs{"",""};
    auto s = vs | hmr::view::join;
    PROVE_CHECK(std::distance(hmr::begin(s), hmr::end(s)) == 0);
    this->check(hmr::begin(s) == hmr::end(s));
    PROVE_CHECK(to_<std::string>(s) == "");
}
