#include <hmr/join.hpp>
#include <hmr/reverse.hpp>
#include "test.hpp"

PROVE_CASE()
{
    std::vector<std::string> vs{"hello","world","!"};
    auto s = vs | hmr::view::join;
    PROVE_CHECK(to_<std::string>(s) == "helloworld!");
    auto rs = s | hmr::view::reverse;
    PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
}

PROVE_CASE()
{
    std::vector<std::string> vs{"hello","","world","","","!"};
    auto s = vs | hmr::view::join;
    PROVE_CHECK(to_<std::string>(s) == "helloworld!");
    auto rs = s | hmr::view::reverse;
    PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
}

PROVE_CASE()
{
    std::vector<std::string> vs{"hello","","world","","","!",""};
    auto s = vs | hmr::view::join;
    PROVE_CHECK(to_<std::string>(s) == "helloworld!");
    auto rs = s | hmr::view::reverse;
    PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
}

PROVE_CASE()
{
    std::vector<std::string> vs{"", "hello","","world","","","!",""};
    auto s = vs | hmr::view::reverse | hmr::view::join;
    PROVE_CHECK(to_<std::string>(s) == "!worldhello");
}

PROVE_CASE()
{
    std::vector<std::string> vs{"", "hello","world","!"};
    auto s = vs | hmr::view::join;
    PROVE_CHECK(to_<std::string>(s) == "helloworld!");
    auto rs = s | hmr::view::reverse;
    PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
}

PROVE_CASE()
{
    std::vector<std::vector<std::string>> vs{{""}, {"h"}, {"ello","world"}, {""}, {"!"}, {""}};
    auto s = vs | hmr::view::join | hmr::view::join;
    PROVE_CHECK(to_<std::string>(s) == "helloworld!");
    auto rs = s | hmr::view::reverse;
    PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
}

PROVE_CASE()
{
    std::vector<std::vector<std::string>> vs{{"h"}, {""}, {"ello","world"}, {""}, {"!"}, {""}};
    auto s = vs | hmr::view::join | hmr::view::join;
    PROVE_CHECK(to_<std::string>(s) == "helloworld!");
    auto rs = s | hmr::view::reverse;
    PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
}


PROVE_CASE()
{
    std::vector<std::string> vs{"", "", "hello","world","!"};
    auto s = vs | hmr::view::join;
    PROVE_CHECK(to_<std::string>(s) == "helloworld!");
    auto rs = s | hmr::view::reverse;
    PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
}

PROVE_CASE()
{
    std::vector<std::string> vs{"hello","world","!", ""};
    auto s = vs | hmr::view::join;
    PROVE_CHECK(to_<std::string>(s) == "helloworld!");
    auto rs = s | hmr::view::reverse;
    PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
}

PROVE_CASE()
{
    std::vector<std::string> vs{"hello","world","!", "", ""};
    auto s = vs | hmr::view::join;
    PROVE_CHECK(to_<std::string>(s) == "helloworld!");
    auto rs = s | hmr::view::reverse;
    PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
}

PROVE_CASE()
{
    std::vector<std::string> vs{"",""};
    auto s = vs | hmr::view::join;
    PROVE_CHECK(std::distance(hmr::begin(s), hmr::end(s)) == 0);
    this->check(hmr::begin(s) == hmr::end(s));
    PROVE_CHECK(to_<std::string>(s) == "");
    auto rs = s | hmr::view::reverse;
    PROVE_CHECK(std::distance(hmr::begin(rs), hmr::end(rs)) == 0);
    this->check(hmr::begin(rs) == hmr::end(rs));
    PROVE_CHECK(to_<std::string>(rs) == "");
}

PROVE_CASE()
{
    std::vector<std::string> vs{"","",""};
    auto s = vs | hmr::view::join;
    PROVE_CHECK(std::distance(hmr::begin(s), hmr::end(s)) == 0);
    this->check(hmr::begin(s) == hmr::end(s));
    PROVE_CHECK(to_<std::string>(s) == "");
    auto rs = s | hmr::view::reverse;
    PROVE_CHECK(std::distance(hmr::begin(rs), hmr::end(rs)) == 0);
    this->check(hmr::begin(rs) == hmr::end(rs));
    PROVE_CHECK(to_<std::string>(rs) == "");
}
