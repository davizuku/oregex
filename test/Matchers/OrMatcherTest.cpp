#include "../catch.hpp"
#include "../../src/Matchables/StringMatchable.hpp"
#include "../../src/Matchers/OrMatcher.hpp"
#include "../../src/Matchers/StarMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Result.hpp"

TEST_CASE("OrMatcher matches any of the specified submatchers in order")
{
    Result *r;
    StringMatchable a("a"), b("b"), c("c");
    StringMatcher ma("a"), mb("b"), mc("c");
    StarMatcher sa(&ma), sb(&mb), sc(&mc);
    vector<MatchableInterface *> input{&a, &b, &c, &c};

    SECTION("Not matches sequence at the end")
    {
        OrMatcher m(vector<MatcherInterface*>{&ma, &mb, &mc});
        REQUIRE(m.match(input, input.size()) == NULL);
        REQUIRE(m.next() == NULL);
    }

    SECTION("Matches with any matcher in the list")
    {
        OrMatcher m(vector<MatcherInterface*>{&ma, &mb, &mc});
        REQUIRE(*(r = m.match(input, 0)) == Result(0, 0));
        delete r;
        REQUIRE(m.next() == NULL);
        REQUIRE(*(r = m.match(input, 1)) == Result(1, 1));
        delete r;
        REQUIRE(m.next() == NULL);
        REQUIRE(*(r = m.match(input, 2)) == Result(2, 2));
        delete r;
        REQUIRE(m.next() == NULL);
    }

    SECTION("Next matches other matchers in the list, in order")
    {
        OrMatcher m(vector<MatcherInterface*>{&sc, &sc});
        REQUIRE(*(r = m.match(input, 2)) == Result(2, 3));
        delete r;
        REQUIRE(*(r = m.next()) == Result(2, 2));
        delete r;
        REQUIRE(*(r = m.next()) == Result(1, 1));
        delete r;
        REQUIRE(*(r = m.next()) == Result(2, 3));
        delete r;
        REQUIRE(*(r = m.next()) == Result(2, 2));
        delete r;
        REQUIRE(*(r = m.next()) == Result(1, 1));
        delete r;
        REQUIRE(m.next() == NULL);
    }
}
