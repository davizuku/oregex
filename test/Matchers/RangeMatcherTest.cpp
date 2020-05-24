#include <forward_list>
#include "../catch.hpp"
#include "../../src/Matchers/RangeMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("RangeMatcher matches from MIN to MAX elements")
{
    StringMatchable a("a"), b("b");
    StringMatcher ma("a");
    RangeMatcher sa(&ma);
    vector<MatchableInterface *> input{&a, &a, &a, &a, &b};

    SECTION("Not matches sequence at the end")
    {
        REQUIRE(sa.match(input, input.size()) == NULL);
    }

    SECTION("Not matches sequence after end")
    {
        REQUIRE(sa.match(input, input.size() + 1) == NULL);
    }

    SECTION("Result of matching 0 or more elements from the beginning")
    {
        RangeMatcher ra24(&ma);
        REQUIRE(*(ra24.match(input, 0)) == Result(0, 3));
        REQUIRE(*(ra24.next()) == Result(0, 2));
        REQUIRE(*(ra24.next()) == Result(0, 1));
        REQUIRE(*(ra24.next()) == Result(0, 0));
        REQUIRE(*(ra24.next()) == Result(-1, -1));
        REQUIRE(ra24.next() == NULL);
    }

    SECTION("Result of matching at least 1 element from the beginning")
    {
        RangeMatcher ra24(&ma, 1);
        REQUIRE(*(ra24.match(input, 0)) == Result(0, 3));
        REQUIRE(*(ra24.next()) == Result(0, 2));
        REQUIRE(*(ra24.next()) == Result(0, 1));
        REQUIRE(*(ra24.next()) == Result(0, 0));
        REQUIRE(ra24.next() == NULL);
    }

    SECTION("Result of matching 2 to 4 elements from the beginning")
    {
        RangeMatcher ra24(&ma, 2, 4);
        REQUIRE(*(ra24.match(input, 0)) == Result(0, 3));
        REQUIRE(*(ra24.next()) == Result(0, 2));
        REQUIRE(*(ra24.next()) == Result(0, 1));
        REQUIRE(ra24.next() == NULL);
    }

    SECTION("Result of matching exactly 3 elements from the beginning")
    {
        RangeMatcher ra24(&ma, 3, 3);
        REQUIRE(*(ra24.match(input, 0)) == Result(0, 2));
        REQUIRE(ra24.next() == NULL);
    }
}
