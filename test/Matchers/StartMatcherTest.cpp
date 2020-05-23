#include "../catch.hpp"
#include "../../src/Matchers/StartMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"
#include "../../src/Result.hpp"

TEST_CASE("StartMatcher matches only with beginning of sequence")
{
    StringMatchable a("a"), b("b"), c("c");
    StartMatcher m;
    vector<MatchableInterface *> input{&a, &b, &c, &c};

    SECTION("Result of matching the first element")
    {
        REQUIRE(*(m.match(input, 0)) == Result(-1, -1));
    }

    SECTION("Result of matching the second element")
    {
        REQUIRE(m.match(input, 1) == NULL);
    }
}
