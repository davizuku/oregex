#include <forward_list>
#include "../catch.hpp"
#include "../../src/Matchers/NamedGroupMatcher.hpp"
#include "../../src/Matchers/StarMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("NamedGroupMatcher returns the elements matched grouped as outputs")
{
    Result *r;
    StringMatchable a("a"), b("b"), c("c"), d("d"), e("e");
    StringMatcher m1("a"), m2("b"), m3("x"), m4("c"), m5("d");
    StarMatcher s1(&m1), s2(&m2), s3(&m3), s4(&m4), s5(&m5);
    NamedGroupMatcher g1("one", &s1), g2("two", &s4), g3("three", &s5);
    vector<MatchableInterface *> input{&a, &b, &c, &c, &d, &e, &d};

    SECTION("Not matches sequence at the end")
    {
        REQUIRE(g1.match(input, input.size()) == NULL);
    }

    SECTION("Not matches sequence after end")
    {
        REQUIRE(g1.match(input, input.size() + 1) == NULL);
    }

    SECTION("Result of matching the first element")
    {
        Result r0(0, 0), r1(-1, -1);
        r0.setOutputs(unordered_map<string, forward_list<MatchableInterface *>>{
            {"one", forward_list<MatchableInterface *>{&a}},
        });
        r1.setOutputs(unordered_map<string, forward_list<MatchableInterface *>>{
            {"one", {}},
        });
        REQUIRE(*(r = g1.match(input, 0)) == r0);
        delete r;
        REQUIRE(*(r = g1.next()) == r1);
        delete r;
    }

    SECTION("Result of matching the second element from the beginning")
    {
        Result r0(-1, -1);
        r0.setOutputs(unordered_map<string, forward_list<MatchableInterface *>>{
            {"two", {}},
        });
        REQUIRE(*(r = g2.match(input, 0)) == r0);
        delete r;
    }

    SECTION("Result of matching the multiple elements")
    {
        Result r0(2, 3), r1(2, 2), r2(1, 1);
        r0.setOutputs(unordered_map<string, forward_list<MatchableInterface *>>{
            {"two", forward_list<MatchableInterface *>{&c, &c}},
        });
        r1.setOutputs(unordered_map<string, forward_list<MatchableInterface *>>{
            {"two", forward_list<MatchableInterface *>{&c}},
        });
        r2.setOutputs(unordered_map<string, forward_list<MatchableInterface *>>{
            {"two", {}},
        });
        REQUIRE(*(r = g2.match(input, 2)) == r0);
        delete r;
        REQUIRE(*(r = g2.next()) == r1);
        delete r;
        REQUIRE(*(r = g2.next()) == r2);
        delete r;
    }

    SECTION("Result of matching last element")
    {
        Result r0(6, 6), r1(5, 5);
        r0.setOutputs(unordered_map<string, forward_list<MatchableInterface *>>{
            {"three", forward_list<MatchableInterface *>{&d}},
        });
        r1.setOutputs(unordered_map<string, forward_list<MatchableInterface *>>{
            {"three", {}},
        });
        REQUIRE(*(r = g3.match(input, 6)) == r0);
        delete r;
        REQUIRE(*(r = g3.next()) == r1);
        delete r;
    }
}

TEST_CASE("NamedGroupMatcher propagates the outputs of internal matcher")
{
    Result *r;
    StringMatchable a("a");
    StringMatcher m1("a");
    NamedGroupMatcher n1("one", &m1), n2("two", &n1);
    vector<MatchableInterface *> input{&a};
    Result expected(
        0,
        0,
        unordered_map<string, forward_list<MatchableInterface *>>{
            {"one", forward_list<MatchableInterface *>{&a}},
            {"two", forward_list<MatchableInterface *>{&a}},
        }
    );
    REQUIRE(*(r = n2.match(input, 0)) == expected);
    delete r;
}
