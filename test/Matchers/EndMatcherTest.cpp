#include "../catch.hpp"
#include "../../src/Matchers/EndMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"
#include "../../src/Result.hpp"

TEST_CASE("EndMatcher matches only with end of sequence")
{
    Result *r;
    StringMatchable a("a"), b("b"), c("c");
    EndMatcher m;
    vector<MatchableInterface *> input{&a, &b, &c, &c};

    SECTION("Result of matching the first element")
    {
        REQUIRE(m.match(input, 0) == NULL);
        REQUIRE(m.next() == NULL);
    }

    SECTION("Result of matching the second element")
    {
        REQUIRE(m.match(input, 1) == NULL);
        REQUIRE(m.next() == NULL);
    }

    SECTION("Result of matching the the last")
    {
        REQUIRE(*(r = m.match(input, 4)) == Result(4, 4));
        delete r;
        REQUIRE(m.next() == NULL);
    }
}
