#include <forward_list>
#include "../catch.hpp"
#include "../../src/Matchers/PlusMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("PlusMatcher matches one or more elements")
{
    Result *r;
    StringMatchable a("a"), b("b"), c("c"), d("d"), e("e");
    StringMatcher ma("a"), mb("b"), mx("x"), mc("c"), md("d");
    PlusMatcher pa(&ma), pb(&mb), px(&mx), pc(&mc), pd(&md);
    vector<MatchableInterface *> input{&a, &b, &c, &c, &d, &e, &d};

    SECTION("Not matches sequence at the end")
    {
        REQUIRE(pa.match(input, input.size()) == NULL);
    }

    SECTION("Not matches sequence after end")
    {
        REQUIRE(pa.match(input, input.size() + 1) == NULL);
    }

    SECTION("Result of matching the first element")
    {
        REQUIRE(*(r = pa.match(input, 0)) == Result(0, 0));
        delete r;
        REQUIRE(pa.next() == NULL);
    }

    SECTION("Result of matching the second element from the beginning")
    {
        REQUIRE(pb.match(input, 0) == NULL);
    }

    SECTION("Result of matching the second element from the element")
    {
        REQUIRE(*(r = pb.match(input, 1)) == Result(1, 1));
        delete r;
        REQUIRE(pb.next() == NULL);
    }

    SECTION("Result of not matching any element from the beginning")
    {
        REQUIRE(px.match(input, 0) == NULL);
    }

    SECTION("Result of not matching any element from position")
    {
        REQUIRE(px.match(input, 2) == NULL);
    }

    SECTION("Result of matching repeated elements from position")
    {
        REQUIRE(*(r = pc.match(input, 2)) == Result(2, 3));
        delete r;
        REQUIRE(*(r = pc.next()) == Result(2, 2));
        delete r;
        REQUIRE(pc.next() == NULL);
    }

    SECTION("Result of matching separated elements from beginning")
    {
        REQUIRE(pd.match(input, 0) == NULL);
    }

    SECTION("Result of matching separated elements from position")
    {
        REQUIRE(*(r = pd.match(input, 4)) == Result(4, 4));
        delete r;
        REQUIRE(pd.next() == NULL);
    }
}
