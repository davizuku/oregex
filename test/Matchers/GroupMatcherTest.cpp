#include "../catch.hpp"
#include <vector>
#include "../../src/Result.hpp"
#include "../../src/Matchers/GroupMatcher.hpp"
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
