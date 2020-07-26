#include <forward_list>
#include "../catch.hpp"
#include "../../src/Matchers/ConditionalLookBehindMatcher.hpp"
#include "../../src/Matchers/GroupMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("ConditionalLookBehindMatcher matches the elements in trueMatcher if condMatcher matches, falseMatcher otherwise.")
{
    Result *r;
    StringMatchable a("a"), b("b"), c("c");
    StringMatcher ma("a"), mb("b"), mc("c");
    GroupMatcher gabc(vector<MatcherInterface *>{&ma, &mb, &mc}),
        gcba(vector<MatcherInterface *>{&mc, &mb, &ma});
    ConditionalLookBehindMatcher m(&ma, &gabc, &gcba);
    vector<MatchableInterface *> input{&a, &b, &c};

    SECTION("Not matches sequence at the end")
    {
        REQUIRE(m.match(input, input.size()) == NULL);
    }

    SECTION("Not matches sequence after end")
    {
        REQUIRE(m.match(input, input.size() + 1) == NULL);
    }

    SECTION("Matches with trueMatch if condMatch matches")
    {
        REQUIRE(*(r = m.match(vector<MatchableInterface *>{&a, &a, &b, &c}, 1)) == Result(1, 3));
        delete r;
        REQUIRE(m.next() == NULL);
    }

    SECTION("Not matches with trueMatch if condMatch matches")
    {
        REQUIRE(m.match(vector<MatchableInterface *>{&b, &a, &b, &c}, 0) == NULL);
        REQUIRE(m.next() == NULL);
    }

    SECTION("Matches with falseMatch if condMatch not matches")
    {
        REQUIRE(*(r = m.match(vector<MatchableInterface *>{&b, &c, &b, &a}, 1)) == Result(1, 3));
        delete r;
        REQUIRE(m.next() == NULL);
    }

    SECTION("Not matches with falseMatch if condMatch not matches")
    {
        REQUIRE(m.match(vector<MatchableInterface *>{&b, &c, &a, &b}, 0) == NULL);
        REQUIRE(m.next() == NULL);
    }
}
