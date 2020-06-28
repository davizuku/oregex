#include <forward_list>
#include "../catch.hpp"
#include "../../src/Matchers/PositiveLookAheadMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("PositiveLookAheadMatcher matches without consuming the input")
{
    StringMatchable a("a"), b("b"), c("c");
    StringMatcher ma("a");
    PositiveLookAheadMatcher m(&ma);
    vector<MatchableInterface *> input{&a, &b, &c};

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
        REQUIRE(*(m.match(input, 0)) == Result(-1, -1));
        REQUIRE(m.next() == NULL);
    }

    SECTION("Result of matching the second element from the beginning")
    {
        REQUIRE(m.match(input, 1) == NULL);
        REQUIRE(m.next() == NULL);
    }
}
