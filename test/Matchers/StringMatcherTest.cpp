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
        REQUIRE(*(m1.match(input, 0)) == Result(-1, 0));
    }

    SECTION("Result of matching the second element from the beginning")
    {
        REQUIRE(m2.match(input, 0) == NULL);
    }

    SECTION("Result of matching the second element from the element")
    {
        REQUIRE(*(m2.match(input, 1)) == Result(-1, 1));
    }

    SECTION("Result of not matching any element")
    {
        REQUIRE(m3.match(input, 0) == NULL);
    }

    SECTION("Result of matching only first of repeated elements")
    {
        REQUIRE(*(m4.match(input, 2)) == Result(-1, 2));
    }
}
