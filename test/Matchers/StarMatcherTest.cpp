#include <forward_list>
#include "../catch.hpp"
#include "../../src/Matchers/StarMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("StarMatcher matches zero or more elements")
{
    Result *r;
    StringMatchable a("a"), b("b"), c("c"), d("d"), e("e");
    StringMatcher m1("a"), m2("b"), m3("x"), m4("c"), m5("d");
    StarMatcher s1(&m1), s2(&m2), s3(&m3), s4(&m4), s5(&m5);
    vector<MatchableInterface *> input{&a, &b, &c, &c, &d, &e, &d};

    SECTION("Not matches sequence at the end")
    {
        REQUIRE(s1.match(input, input.size()) == NULL);
    }

    SECTION("Not matches sequence after end")
    {
        REQUIRE(s1.match(input, input.size() + 1) == NULL);
    }

    SECTION("Result of matching the first element")
    {
        REQUIRE(*(r = s1.match(input, 0)) == Result(0, 0));
        delete r;
        REQUIRE(*(r = s1.next()) == Result(-1, -1));
        delete r;
    }

    SECTION("Result of matching the second element from the beginning")
    {
        REQUIRE(*(r = s2.match(input, 0)) == Result(-1, -1));
        delete r;
    }

    SECTION("Result of matching the second element from the element")
    {
        REQUIRE(*(r = s2.match(input, 1)) == Result(1, 1));
        delete r;
        REQUIRE(*(r = s2.next()) == Result(0, 0));
        delete r;
    }

    SECTION("Result of not matching any element from the beginning")
    {
        REQUIRE(*(r = s3.match(input, 0)) == Result(-1, -1));
        delete r;
    }

    SECTION("Result of not matching any element from position")
    {
        REQUIRE(*(r = s3.match(input, 2)) == Result(1, 1));
        delete r;
    }

    SECTION("Result of matching repeated elements from position")
    {
        REQUIRE(*(r = s4.match(input, 2)) == Result(2, 3));
        delete r;
        REQUIRE(*(r = s4.next()) == Result(2, 2));
        delete r;
        REQUIRE(*(r = s4.next()) == Result(1, 1));
        delete r;
    }

    SECTION("Result of matching separated elements from beginning")
    {
        REQUIRE(*(r = s5.match(input, 0)) == Result(-1, -1));
        delete r;
    }

    SECTION("Result of matching separated elements from position")
    {
        REQUIRE(*(r = s5.match(input, 4)) == Result(4, 4));
        delete r;
        REQUIRE(*(r = s5.next()) == Result(3, 3));
        delete r;
    }
}
