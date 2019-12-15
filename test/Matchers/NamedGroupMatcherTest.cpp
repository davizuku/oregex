#include <forward_list>
#include "../catch.hpp"
#include "../../src/Matchers/NamedGroupMatcher.hpp"
#include "../../src/Matchers/StarMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("NamedGroupMatcher returns the elements matched grouped as outputs")
{
    StringMatchable a("a"), b("b"), c("c"), d("d"), e("e");
    StringMatcher m1("a"), m2("b"), m3("x"), m4("c"), m5("d");
    StarMatcher s1(&m1), s2(&m2), s3(&m3), s4(&m4), s5(&m5);
    NamedGroupMatcher g1("one", &s1), g2("two", &s4), g3("three", &s5);
    vector<MatchableInterface *> input{&a, &b, &c, &c, &d, &e, &d};

    SECTION("Result of matching the first element")
    {
        Result r0(0), r1(-1);
        r0.setOutputs(map<string, forward_list<MatchableInterface *>>{
            {"one", forward_list<MatchableInterface *>{&a}},
        });
        r1.setOutputs(map<string, forward_list<MatchableInterface *>>{
            {"one", {}},
        });
        forward_list<Result> expected{r0, r1};
        REQUIRE(g1.match(input, 0) == expected);
    }

    SECTION("Result of matching the second element from the beginning")
    {
        Result r0(-1);
        r0.setOutputs(map<string, forward_list<MatchableInterface *>>{
            {"two", {}},
        });
        forward_list<Result> expected{r0};
        REQUIRE(g2.match(input, 0) == expected);
    }

    SECTION("Result of matching the multiple elements")
    {
        Result r0(3), r1(2), r2(1);
        r0.setOutputs(map<string, forward_list<MatchableInterface *>>{
            {"two", forward_list<MatchableInterface *>{&c, &c}},
        });
        r1.setOutputs(map<string, forward_list<MatchableInterface *>>{
            {"two", forward_list<MatchableInterface *>{&c}},
        });
        r2.setOutputs(map<string, forward_list<MatchableInterface *>>{
            {"two", {}},
        });
        forward_list<Result> expected{r0, r1, r2};
        REQUIRE(g2.match(input, 2) == expected);
    }

    SECTION("Result of matching last element")
    {
        Result r0(6), r1(5);
        r0.setOutputs(map<string, forward_list<MatchableInterface *>>{
            {"three", forward_list<MatchableInterface *>{&d}},
        });
        r1.setOutputs(map<string, forward_list<MatchableInterface *>>{
            {"three", {}},
        });
        forward_list<Result> expected{r0, r1};
        REQUIRE(g3.match(input, 6) == expected);
    }
}