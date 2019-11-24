#include "../catch.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("StringMatcher matches only with same strings")
{
    StringMatchable a("a"), b("b"), c("c");
    StringMatcher m1("a"), m2("b"), m3("x"), m4("c");
    vector<MatchableInterface *> input{&a, &b, &c, &c};

    SECTION("Result of matching the first element")
    {
        forward_list<Result> expected{Result(0)};
        REQUIRE(m1.match(input, 0) == expected);
    }

    SECTION("Result of matching the second element from the beginning")
    {
        forward_list<Result> expected{};
        REQUIRE(m2.match(input, 0) == expected);
    }

    SECTION("Result of matching the second element from the element")
    {
        forward_list<Result> expected{Result(1)};
        REQUIRE(m2.match(input, 1) == expected);
    }

    SECTION("Result of not matching any element")
    {
        forward_list<Result> expected;
        REQUIRE(m3.match(input, 0) == expected);
    }

    SECTION("Result of matching only first of repeated elements")
    {
        forward_list<Result> expected{Result(2)};
        REQUIRE(m4.match(input, 2) == expected);
    }
}
