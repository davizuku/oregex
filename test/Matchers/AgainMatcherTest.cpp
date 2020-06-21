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

    SECTION("Matches if a result exists with the same sequence")
    {
        forward_list<Result> prevResults = {
            Result(0, 3, unordered_map<string, forward_list<MatchableInterface*>>{
                {"other", forward_list<MatchableInterface*>{&a, &b, &c, &a}}
            }),
            Result(0, 2, unordered_map<string, forward_list<MatchableInterface*>>{
                {"repeat", forward_list<MatchableInterface*>{&a, &b, &c}}
            }),
        };
        REQUIRE(*(m.match(input, 0, prevResults)) == Result(0, 2));
        REQUIRE(m.next() == NULL);
        REQUIRE(*(m.match(input, 3, prevResults)) == Result(3, 5));
        REQUIRE(m.next() == NULL);
    }
}
