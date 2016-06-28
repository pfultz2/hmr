
#include <prove.hpp>
#include <algorithm>

template<class R, class Val>
prove::predicate_result range_equal(R&& actual, std::initializer_list<Val> expected)
{
    using std::begin;
    using std::end;

    prove::predicate_result r{true};

    auto first1 = begin(actual);
    auto last1 = end(actual);
    auto first2 = begin(expected);
    auto last2 = end(expected);

    std::stringstream ss1, ss2;

    ss1 << "{";
    ss2 << "{";

    for (; first1 != last1 and first2 != last2; ++first1, ++first2) 
    {
        ss1 << *first1 << ", ";
        ss2 << *first2 << ", ";
        if (*first1 != *first2) 
        {
            r.result() = false;
        }
    }

    ss1 << "}";
    ss2 << "}";

    r.result() = r.result() && first1 == last1 && first2 == last2;
    if (!r) r << ss1.str() << " != " << ss2.str();
    return r;
}

template<class R, class T>
R to_(T&& x)
{
    using std::begin;
    using std::end;
    return R(begin(x), end(x));
}

int main() 
{
    prove::run();
}
