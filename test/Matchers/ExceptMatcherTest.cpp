#include "../catch.hpp"
#include "../../src/Matchers/ExceptMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("ExceptMatcher matches any element except for those in a list")
{
    StringMatchable a("a"), b("b"), c("c");
    StringMatcher ma("a"), mb("b"), mc("c");
    ExceptMatcher m(vector<MatcherInterface*>{&ma, &mb});
    vector<MatchableInterface *> input{&a, &b, &c, &a, &b, &c};

    SECTION("Not matches sequence at the end")
    {
        REQUIRE(m.match(input, input.size()) == NULL);
    }

    SECTION("Not matches sequence after end")
    {
        REQUIRE(m.match(input, input.size() + 1) == NULL);
    }

    SECTION("Matches if the matchable matches none of the specified matchers")
    {
        REQUIRE(*(m.match(input, 2)) == Result(2, 2));
        REQUIRE(m.next() == NULL);
    }

    SECTION("Not matches if the matchable matches one of the specified matchers")
    {
        REQUIRE(m.match(input, 0) == NULL);
        REQUIRE(m.next() == NULL);
    }
}
