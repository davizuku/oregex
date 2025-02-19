#include <forward_list>
#include "../catch.hpp"
#include "../../src/Matchers/NegativeLookAheadMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("NegativeLookAheadMatcher matches without consuming the input")
{
    Result *r;
    StringMatchable a("a"), b("b"), c("c");
    StringMatcher ma("a");
    NegativeLookAheadMatcher m(&ma);
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
        REQUIRE(m.match(input, 0) == NULL);
        REQUIRE(m.next() == NULL);
    }

    SECTION("Result of matching the second element from the beginning")
    {
        REQUIRE(*(r = m.match(input, 1)) == Result(0, 0));
        delete r;
        REQUIRE(m.next() == NULL);
    }
}
