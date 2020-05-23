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
}
