#include "../catch.hpp"
#include "../../src/Matchers/AnyMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"
#include "../../src/Result.hpp"

TEST_CASE("AnyMatcher matches only with beginning of sequence")
{
    Result *r;
    StringMatchable a("a"), b("b"), c("c");
    AnyMatcher m;
    vector<MatchableInterface *> input{&a, &b, &c, &c};

    SECTION("Result an element from the beginning")
    {
        REQUIRE(*(r = m.match(input, 0)) == Result(0, 0));
        delete r;
        REQUIRE(m.next() == NULL);
    }

    SECTION("Result of matching the second element")
    {
        REQUIRE(*(r = m.match(input, 1)) == Result(1, 1));
        delete r;
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
