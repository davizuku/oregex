#include "../catch.hpp"
#include "../../src/Matchers/StartMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"
#include "../../src/Result.hpp"

TEST_CASE("StartMatcher matches only with beginning of sequence")
{
    Result *r;
    StringMatchable a("a"), b("b"), c("c");
    StartMatcher m;
    vector<MatchableInterface *> input{&a, &b, &c, &c};

    SECTION("Result of matching the first element")
    {
        REQUIRE(*(r = m.match(input, 0)) == Result(-1, -1));
        delete r;
        REQUIRE(m.next() == NULL);
    }

    SECTION("Result of matching the second element")
    {
        REQUIRE(m.match(input, 1) == NULL);
        REQUIRE(m.next() == NULL);
    }

    SECTION("Not matches sequence at the end")
    {
        REQUIRE(m.match(input, input.size()) == NULL);
        REQUIRE(m.next() == NULL);
    }

    SECTION("Not matches sequence after end")
    {
        REQUIRE(m.match(input, input.size() + 1) == NULL);
        REQUIRE(m.next() == NULL);
    }
}
