#include <hmr/join.hpp>
#include <hmr/reverse.hpp>
#include "test.hpp"

#include <vector>
#include <list>

template<template<class...> class Container>
struct join_test_suite
{
    typedef void type;
    struct test_0 : prove::test_case<test_0>
    {
        void test()
        {
            Container<std::string> vs{"hello","world","!"};
            auto s = vs | hmr::view::join;
            PROVE_CHECK(to_<std::string>(s) == "helloworld!");
            auto rs = s | hmr::view::reverse;
            PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
        }
    };


    struct test_1 : prove::test_case<test_1>
    {
        void test()
        {
            Container<std::string> vs{"hello","","world","","","!"};
            auto s = vs | hmr::view::join;
            PROVE_CHECK(to_<std::string>(s) == "helloworld!");
            auto rs = s | hmr::view::reverse;
            PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
        }
    };


    struct test_2 : prove::test_case<test_2>
    {
        void test()
        {
            Container<std::string> vs{"hello","","world","","","!",""};
            auto s = vs | hmr::view::join;
            PROVE_CHECK(to_<std::string>(s) == "helloworld!");
            auto rs = s | hmr::view::reverse;
            PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
        }
    };


    struct test_3 : prove::test_case<test_3>
    {
        void test()
        {
            Container<std::string> vs{"", "hello","","world","","","!",""};
            auto s = vs | hmr::view::reverse | hmr::view::join;
            PROVE_CHECK(to_<std::string>(s) == "!worldhello");
        }
    };


    struct test_4 : prove::test_case<test_4>
    {
        void test()
        {
            Container<std::string> vs{"", "hello","world","!"};
            auto s = vs | hmr::view::join;
            PROVE_CHECK(to_<std::string>(s) == "helloworld!");
            auto rs = s | hmr::view::reverse;
            PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
        }
    };


    struct test_5 : prove::test_case<test_5>
    {
        void test()
        {
            Container<Container<std::string>> vs{{""}, {"h"}, {"ello","world"}, {""}, {"!"}, {""}};
            auto s = vs | hmr::view::join | hmr::view::join;
            PROVE_CHECK(to_<std::string>(s) == "helloworld!");
            auto rs = s | hmr::view::reverse;
            PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
        }
    };


    struct test_6 : prove::test_case<test_6>
    {
        void test()
        {
            Container<Container<std::string>> vs{{"h"}, {""}, {"ello","world"}, {""}, {"!"}, {""}};
            auto s = vs | hmr::view::join | hmr::view::join;
            PROVE_CHECK(to_<std::string>(s) == "helloworld!");
            auto rs = s | hmr::view::reverse;
            PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
        }
    };


    struct test_7 : prove::test_case<test_7>
    {
        void test()
        {
            Container<Container<Container<std::string>>> vs{{{"h"}, {""}}, {{"ello","world"}, {""}}, {{"!"}, {""}}};
            auto s = vs | hmr::view::join | hmr::view::join | hmr::view::join;
            PROVE_CHECK(to_<std::string>(s) == "helloworld!");
            auto rs = s | hmr::view::reverse;
            PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
        }
    };


    struct test_8 : prove::test_case<test_8>
    {
        void test()
        {
            Container<Container<Container<std::string>>> vs{{}, {{"h"}, {""}}, {{"ello","world"}, {""}}, {{"!"}, {""}}, {}};
            auto s = vs | hmr::view::join | hmr::view::join | hmr::view::join;
            PROVE_CHECK(to_<std::string>(s) == "helloworld!");
            auto rs = s | hmr::view::reverse;
            PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
        }
    };



    struct test_9 : prove::test_case<test_9>
    {
        void test()
        {
            Container<std::string> vs{"", "", "hello","world","!"};
            auto s = vs | hmr::view::join;
            PROVE_CHECK(to_<std::string>(s) == "helloworld!");
            auto rs = s | hmr::view::reverse;
            PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
        }
    };


    struct test_10 : prove::test_case<test_10>
    {
        void test()
        {
            Container<std::string> vs{"hello","world","!", ""};
            auto s = vs | hmr::view::join;
            PROVE_CHECK(to_<std::string>(s) == "helloworld!");
            auto rs = s | hmr::view::reverse;
            PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
        }
    };


    struct test_11 : prove::test_case<test_11>
    {
        void test()
        {
            Container<std::string> vs{"hello","world","!", "", ""};
            auto s = vs | hmr::view::join;
            PROVE_CHECK(to_<std::string>(s) == "helloworld!");
            auto rs = s | hmr::view::reverse;
            PROVE_CHECK(to_<std::string>(rs) == "!dlrowolleh");
        }
    };


    struct test_12 : prove::test_case<test_12>
    {
        void test()
        {
            Container<std::string> vs{"",""};
            auto s = vs | hmr::view::join;
            PROVE_CHECK(hmr::distance(hmr::begin(s), hmr::end(s)) == 0);
            this->check(hmr::begin(s) == hmr::end(s));
            PROVE_CHECK(to_<std::string>(s) == "");
            auto rs = s | hmr::view::reverse;
            PROVE_CHECK(hmr::distance(hmr::begin(rs), hmr::end(rs)) == 0);
            this->check(hmr::begin(rs) == hmr::end(rs));
            PROVE_CHECK(to_<std::string>(rs) == "");
        }   

    };

    struct test_13 : prove::test_case<test_13>
    {
        void test()
        {
            Container<std::string> vs{"","",""};
            auto s = vs | hmr::view::join;
            PROVE_CHECK(hmr::distance(hmr::begin(s), hmr::end(s)) == 0);
            this->check(hmr::begin(s) == hmr::end(s));
            PROVE_CHECK(to_<std::string>(s) == "");
            auto rs = s | hmr::view::reverse;
            PROVE_CHECK(hmr::distance(hmr::begin(rs), hmr::end(rs)) == 0);
            this->check(hmr::begin(rs) == hmr::end(rs));
            PROVE_CHECK(to_<std::string>(rs) == "");
        }   

    };
};

template struct join_test_suite<std::vector>;
template struct join_test_suite<std::list>;

