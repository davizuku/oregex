#include <forward_list>
#include "../catch.hpp"
#include "../../src/Matchers/StarMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("StarMatcher matches zero or more elements")
{
    StringMatchable a("a"), b("b"), c("c"), d("d"), e("e");
    StringMatcher m1("a"), m2("b"), m3("x"), m4("c"), m5("d");
    StarMatcher s1(&m1), s2(&m2), s3(&m3), s4(&m4), s5(&m5);
    vector<MatchableInterface *> input{&a, &b, &c, &c, &d, &e, &d};

    SECTION("Result of matching the first element")
    {
        forward_list<Result> expected{Result(0), Result(-1)};
        REQUIRE(s1.match(input, 0) == expected);
    }

    SECTION("Result of matching the second element from the beginning")
    {
        forward_list<Result> expected{Result(-1)};
        REQUIRE(s2.match(input, 0) == expected);
    }

    SECTION("Result of matching the second element from the element")
    {
        forward_list<Result> expected{Result(1), Result(0)};
        REQUIRE(s2.match(input, 1) == expected);
    }

    SECTION("Result of not matching any element from the beginning")
    {
        forward_list<Result> expected{Result(-1)};
        REQUIRE(s3.match(input, 0) == expected);
    }

    SECTION("Result of not matching any element from position")
    {
        forward_list<Result> expected{Result(1)};
        REQUIRE(s3.match(input, 2) == expected);
    }

    SECTION("Result of matching repeated elements from position")
    {
        forward_list<Result> expected{Result(3), Result(2), Result(1)};
        REQUIRE(s4.match(input, 2) == expected);
    }

    SECTION("Result of matching separated elements from beginning")
    {
        forward_list<Result> expected{Result(-1)};
        REQUIRE(s5.match(input, 0) == expected);
    }

    SECTION("Result of matching separated elements from position")
    {
        forward_list<Result> expected{Result(4), Result(3)};
        REQUIRE(s5.match(input, 4) == expected);
    }
}
