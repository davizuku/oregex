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
    Result *r;
    StringMatchable a("a"), b("b"), c("c"), d("d"), e("e");
    StringMatcher m1("a"), m2("b"), m3("x"), m4("c"), m5("d"), m6("e");
    StarMatcher s1(&m1), s2(&m2), s3(&m3), s4(&m4), s5(&m5);
    vector<MatchableInterface *> input{&a, &b, &c, &c, &d, &e, &d};

    SECTION("Not matches sequence at the end")
    {
        GroupMatcher gm(vector<MatcherInterface *>{&m1, &m2, &m4});
        REQUIRE(gm.match(input, input.size()) == NULL);
    }

    SECTION("Not matches sequence after end")
    {
        GroupMatcher gm(vector<MatcherInterface *>{&m1, &m2, &m4});
        REQUIRE(gm.match(input, input.size()+1) == NULL);
    }

    SECTION("Matches sequence in the beginning (/abc/ -> abccded)")
    {
        GroupMatcher gm(vector<MatcherInterface *>{&m1, &m2, &m4});
        REQUIRE(*(r = gm.match(input, 0)) == Result(0, 2));
        delete r;
    }

    SECTION("Matches sequence in the middle (/c*/ -> abccded)")
    {
        GroupMatcher gm(vector<MatcherInterface *>{&s4});
        REQUIRE(*(r = gm.match(input, 2)) == Result(2, 3));
        delete r;
        REQUIRE(*(r = gm.next()) == Result(2, 2));
        delete r;
        REQUIRE(*(r = gm.next()) == Result(1, 1));
        delete r;
    }

    SECTION("Matches sequence in the middle (/cc/ -> abccded)")
    {
        GroupMatcher gm(vector<MatcherInterface *>{&m4, &m4});
        REQUIRE(*(r = gm.match(input, 2)) == Result(2, 3));
        delete r;
    }

    SECTION("Matches sequence in the end (/ded/ -> abccded)")
    {
        GroupMatcher gm(vector<MatcherInterface *>{&m5, &m6, &m5});
        REQUIRE(*(r = gm.match(input, 4)) == Result(4, 6));
        delete r;
    }

    SECTION("Not matches sequence (/x/ -> abccded)")
    {
        GroupMatcher gm(vector<MatcherInterface *>{&m3});
        REQUIRE(gm.match(input, 0) == NULL);
    }
}

TEST_CASE("GroupMatcher joins the results of the specified elements")
{
    Result *r;
    StringMatcher o("o");
    StarMatcher so(&o);
    NamedGroupMatcher ngm("outputs", &so);
    GroupMatcher matcher(vector<MatcherInterface *>{&ngm, &o, &o});
    StringMatchable o1("o"), o2("o"), o3("o"), o4("o"), o5("o"), o6("o");

    SECTION("Only mandatory input does not return output")
    {
        Result expected = Result(
            0,
            1,
            unordered_map<string, forward_list<MatchableInterface *>>{
                {"outputs", forward_list<MatchableInterface *>{}}
            }
        );
        vector<MatchableInterface *> input{&o1, &o2};
        REQUIRE(*(r = matcher.match(input, 0)) == expected);
        delete r;
    }

    SECTION("Not mandatory input is returned as output")
    {
        Result r1 = Result(
            0,
            2,
            unordered_map<string, forward_list<MatchableInterface *>>{
                {"outputs", forward_list<MatchableInterface *>{&o1}}
            }
        );
        Result r2 = Result(
            0,
            1,
            unordered_map<string, forward_list<MatchableInterface *>>{
                {"outputs", forward_list<MatchableInterface *>{}}
            }
        );
        vector<MatchableInterface *> input{&o1, &o2, &o3};
        REQUIRE(*(r = matcher.match(input, 0)) == r1);
        delete r;
        REQUIRE(*(r = matcher.next()) == r2);
        delete r;
    }

    SECTION("Greediness from optional part")
    {
        Result r1 = Result(
            0,
            5,
            unordered_map<string, forward_list<MatchableInterface *>>{
                {"outputs", forward_list<MatchableInterface *>{&o1, &o2, &o3, &o4}}
            }
        );
        Result r2 = Result(
            0,
            4,
            unordered_map<string, forward_list<MatchableInterface *>>{
                {"outputs", forward_list<MatchableInterface *>{&o1, &o2, &o3}}
            }
        );
        Result r3 = Result(
            0,
            3,
            unordered_map<string, forward_list<MatchableInterface *>>{
                {"outputs", forward_list<MatchableInterface *>{&o1, &o2}}
            }
        );
        Result r4 = Result(
            0,
            2,
            unordered_map<string, forward_list<MatchableInterface *>>{
                {"outputs", forward_list<MatchableInterface *>{&o1}}
            }
        );
        Result r5 = Result(
            0,
            1,
            unordered_map<string, forward_list<MatchableInterface *>>{
                {"outputs", forward_list<MatchableInterface *>{}}
            }
        );
        vector<MatchableInterface *> input{&o1, &o2, &o3, &o4, &o5, &o6};
        REQUIRE(*(r = matcher.match(input, 0)) == r1);
        delete r;
        REQUIRE(*(r = matcher.next()) == r2);
        delete r;
        REQUIRE(*(r = matcher.next()) == r3);
        delete r;
        REQUIRE(*(r = matcher.next()) == r4);
        delete r;
        REQUIRE(*(r = matcher.next()) == r5);
        delete r;
    }
}
