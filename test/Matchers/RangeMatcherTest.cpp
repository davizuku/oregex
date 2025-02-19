#include <forward_list>
#include "../catch.hpp"
#include "../../src/Matchers/RangeMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("RangeMatcher matches from MIN to MAX elements")
{
    Result *r;
    StringMatchable a("a"), b("b");
    StringMatcher ma("a"), mb("b");
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
        REQUIRE(*(r = sa.match(input, 0)) == Result(0, 3));
        delete r;
        REQUIRE(*(r = sa.next()) == Result(0, 2));
        delete r;
        REQUIRE(*(r = sa.next()) == Result(0, 1));
        delete r;
        REQUIRE(*(r = sa.next()) == Result(0, 0));
        delete r;
        REQUIRE(*(r = sa.next()) == Result(-1, -1));
        delete r;
        REQUIRE(sa.next() == NULL);
    }

    SECTION("Result of matching at least 1 element from the beginning")
    {
        RangeMatcher ra1(&ma, 1);
        REQUIRE(*(r = ra1.match(input, 0)) == Result(0, 3));
        delete r;
        REQUIRE(*(r = ra1.next()) == Result(0, 2));
        delete r;
        REQUIRE(*(r = ra1.next()) == Result(0, 1));
        delete r;
        REQUIRE(*(r = ra1.next()) == Result(0, 0));
        delete r;
        REQUIRE(ra1.next() == NULL);
    }

    SECTION("Result of matching 2 to 4 elements from the beginning")
    {
        RangeMatcher ra24(&ma, 2, 4);
        REQUIRE(*(r = ra24.match(input, 0)) == Result(0, 3));
        delete r;
        REQUIRE(*(r = ra24.next()) == Result(0, 2));
        delete r;
        REQUIRE(*(r = ra24.next()) == Result(0, 1));
        delete r;
        REQUIRE(ra24.next() == NULL);
    }

    SECTION("Result of matching exactly 3 elements from the beginning")
    {
        RangeMatcher ra33(&ma, 3, 3);
        REQUIRE(*(r = ra33.match(input, 0)) == Result(0, 2));
        delete r;
        REQUIRE(ra33.next() == NULL);
    }

    SECTION("Result of not matching exactly 5 elements from the beginning")
    {
        RangeMatcher ra55(&ma, 5, 5);
        REQUIRE(ra55.match(input, 0) == NULL);
    }

    SECTION("Result of matching at least 0 elements from the beginning")
    {
        RangeMatcher rb(&mb);
        REQUIRE(*(r = rb.match(input, 0)) == Result(-1, -1));
        delete r;
        REQUIRE(rb.next() == NULL);
    }

    SECTION("Result of not matching at least 1 element from the beginning")
    {
        RangeMatcher rb1(&mb, 1);
        REQUIRE(rb1.match(input, 0) == NULL);
    }
}
