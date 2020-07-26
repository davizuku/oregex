#include <forward_list>
#include "../catch.hpp"
#include "../../src/Matchers/ConditionMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("ConditionMatcher matches the elements of trueMatcher if the specified group was matched, falseMatcher otherwise")
{
    Result *r;
    StringMatchable a("a"), b("b");
    StringMatcher ma("a"), mb("b");
    ConditionMatcher m("check", &ma, &mb);
    vector<MatchableInterface *> input{&a, &b};

    SECTION("Not matches sequence at the end")
    {
        REQUIRE(m.match(input, input.size()) == NULL);
    }

    SECTION("Not matches sequence after end")
    {
        REQUIRE(m.match(input, input.size() + 1) == NULL);
    }

    SECTION("Matches with true matcher if group matched")
    {
        forward_list<Result> prevResults = {
            Result(0, 3, unordered_map<string, forward_list<MatchableInterface*>>{
                {"other", forward_list<MatchableInterface*>{&a, &b}}
            }),
            Result(0, 2, unordered_map<string, forward_list<MatchableInterface*>>{
                {"check", forward_list<MatchableInterface*>{&a, &b}}
            }),
        };
        REQUIRE(*(r = m.match(input, 0, prevResults)) == Result(0, 0));
        delete r;
        REQUIRE(m.next() == NULL);
        REQUIRE(m.match(input, 1, prevResults) == NULL);
        REQUIRE(m.next() == NULL);
    }

    SECTION("Matches with false matcher if group not matched")
    {
        REQUIRE(m.match(input, 0) == NULL);
        REQUIRE(m.next() == NULL);
        REQUIRE(*(r = m.match(input, 1)) == Result(1, 1));
        delete r;
        REQUIRE(m.next() == NULL);
    }
}
