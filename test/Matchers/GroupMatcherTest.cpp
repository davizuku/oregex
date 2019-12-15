#include "../catch.hpp"
#include <vector>
#include "../../src/Result.hpp"
#include "../../src/Matchers/GroupMatcher.hpp"
#include "../../src/Matchers/NamedGroupMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchers/StarMatcher.hpp"
#include "../../src/Matchers/MatcherInterface.hpp"
#include "../../src/Matchables/StringMatchable.hpp"
#include "../../src/Matchables/MatchableInterface.hpp"

TEST_CASE("GroupMatcher is built from Matchers and is executed on Matchables")
{
    StringMatchable a("a"), b("b"), c("c"), d("d"), e("e");
    StringMatcher m1("a"), m2("b"), m3("x"), m4("c"), m5("d"), m6("e");
    StarMatcher s1(&m1), s2(&m2), s3(&m3), s4(&m4), s5(&m5);
    vector<MatchableInterface *> input{&a, &b, &c, &c, &d, &e, &d};

    SECTION("Matches sequence in the beginning (/abc/ -> abccded)")
    {
        GroupMatcher gm(vector<MatcherInterface *>{&m1, &m2, &m4});
        forward_list<Result> expected{Result(2)};
        REQUIRE(gm.match(input, 0) == expected);
    }

    SECTION("Matches sequence in the middle (/c*/ -> abccded)")
    {
        GroupMatcher gm(vector<MatcherInterface *>{&s4});
        forward_list<Result> expected{Result(3), Result(2), Result(1)};
        REQUIRE(gm.match(input, 2) == expected);
    }

    SECTION("Matches sequence in the middle (/cc/ -> abccded)")
    {
        GroupMatcher gm(vector<MatcherInterface *>{&m4, &m4});
        forward_list<Result> expected{Result(3)};
        REQUIRE(gm.match(input, 2) == expected);
    }

    SECTION("Matches sequence in the end (/ded/ -> abccded)")
    {
        GroupMatcher gm(vector<MatcherInterface *>{&m5, &m6, &m5});
        forward_list<Result> expected{Result(6)};
        REQUIRE(gm.match(input, 4) == expected);
    }

    SECTION("Not matches sequence (/x/ -> abccded)")
    {
        GroupMatcher gm(vector<MatcherInterface *>{&m3});
        forward_list<Result> expected{};
        REQUIRE(gm.match(input, 0) == expected);
    }
}

TEST_CASE("GroupMatcher joins the results of the specified elements")
{
    StringMatcher o("o");
    GroupMatcher matcher(vector<MatcherInterface *>{
        new NamedGroupMatcher("outputs", new StarMatcher(&o)),
        &o,
        &o
    });
    StringMatchable o1("o"), o2("o"), o3("o"), o4("o"), o5("o"), o6("o");

    SECTION("Only mandatory input does not return output")
    {
        forward_list<Result> expected{
            Result(
                1,
                map<string, forward_list<MatchableInterface *>>{
                    {"outputs", forward_list<MatchableInterface *>{}}
                }
            )
        };
        vector<MatchableInterface *> input{&o1, &o2};
        REQUIRE(matcher.match(input, 0) == expected);
    }

    SECTION("Not mandatory input is returned as output")
    {
        forward_list<Result> expected{
            Result(
                2,
                map<string, forward_list<MatchableInterface *>>{
                    {"outputs", forward_list<MatchableInterface *>{&o1}}
                }
            ),
            Result(
                1,
                map<string, forward_list<MatchableInterface *>>{
                    {"outputs", forward_list<MatchableInterface *>{}}
                }
            ),
        };
        vector<MatchableInterface *> input{&o1, &o2, &o3};
        REQUIRE(matcher.match(input, 0) == expected);
    }

    SECTION("Greediness from optional part")
    {
        forward_list<Result> expected{
            Result(
                5,
                map<string, forward_list<MatchableInterface *>>{
                    {"outputs", forward_list<MatchableInterface *>{&o1, &o2, &o3, &o4}}
                }
            ),
            Result(
                4,
                map<string, forward_list<MatchableInterface *>>{
                    {"outputs", forward_list<MatchableInterface *>{&o1, &o2, &o3}}
                }
            ),
            Result(
                3,
                map<string, forward_list<MatchableInterface *>>{
                    {"outputs", forward_list<MatchableInterface *>{&o1, &o2}}
                }
            ),
            Result(
                2,
                map<string, forward_list<MatchableInterface *>>{
                    {"outputs", forward_list<MatchableInterface *>{&o1}}
                }
            ),
            Result(
                1,
                map<string, forward_list<MatchableInterface *>>{
                    {"outputs", forward_list<MatchableInterface *>{}}
                }
            ),
        };
        vector<MatchableInterface *> input{&o1, &o2, &o3, &o4, &o5, &o6};
        REQUIRE(matcher.match(input, 0) == expected);
    }
}