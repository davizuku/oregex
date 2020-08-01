#include <forward_list>
#include "../catch.hpp"
#include "../../src/Matchers/PositiveLookBehindMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("PositiveLookBehindMatcher matches without consuming the input")
{
    Result *r;
    StringMatchable a("a"), b("b"), c("c");
    StringMatcher ma("a"), mb("b"), mc("c");
    PositiveLookBehindMatcher m(&ma);
    vector<MatchableInterface *> input{&a, &a, &b, &c};

    SECTION("Not matches sequence at the end")
    {
        REQUIRE(m.match(input, input.size()) == NULL);
    }

    SECTION("Not matches sequence after end")
    {
        REQUIRE(m.match(input, input.size() + 1) == NULL);
    }

    SECTION("Result of matching the first element")
    {
        REQUIRE(m.match(input, 0) == NULL);
        REQUIRE(m.next() == NULL);
    }

    SECTION("Result of matching in middle positions")
    {
        REQUIRE(*(r = m.match(input, 1)) == Result(0, 0));
        delete r;
        REQUIRE(m.next() == NULL);
        REQUIRE(*(r = m.match(input, 2)) == Result(1, 1));
        delete r;
        REQUIRE(m.next() == NULL);
    }

    SECTION("Result of not matching with given input")
    {
        REQUIRE(m.match(input, 3) == NULL);
        REQUIRE(m.next() == NULL);
    }
}
