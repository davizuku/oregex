#include <forward_list>
#include "../catch.hpp"
#include "../../src/Matchers/ExactlyMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("ExactlyMatcher matches exactly N elements")
{
    Result *r;
    StringMatchable a("a"), b("b");
    StringMatcher ma("a"), mb("b");
    ExactlyMatcher m1(&ma, 1);
    vector<MatchableInterface *> input{&a, &a, &a, &a, &b};

    SECTION("Not matches sequence at the end")
    {
        REQUIRE(m1.match(input, input.size()) == NULL);
    }

    SECTION("Not matches sequence after end")
    {
        REQUIRE(m1.match(input, input.size() + 1) == NULL);
    }

    SECTION("Result of matching exactly 3 elements from the beginning")
    {
        ExactlyMatcher m3(&ma, 3);
        REQUIRE(*(r = m3.match(input, 0)) == Result(0, 2));
        delete r;
        REQUIRE(m3.next() == NULL);
    }

    SECTION("Result of not matching exactly 5 elements from the beginning")
    {
        ExactlyMatcher m5(&ma, 5);
        REQUIRE(m5.match(input, 0) == NULL);
    }
}
