#include "../catch.hpp"
#include "../../src/Matchers/AgainMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("AgainMatcher matches only with same strings")
{
    StringMatchable a("a"), b("b"), c("c");
    AgainMatcher m("repeat");
    vector<MatchableInterface *> input{&a, &b, &c, &a, &b, &c};

    SECTION("Not matches sequence at the end")
    {
        REQUIRE(m.match(input, input.size()) == NULL);
    }

    SECTION("Not matches sequence after end")
    {
        REQUIRE(m.match(input, input.size() + 1) == NULL);
    }
}
