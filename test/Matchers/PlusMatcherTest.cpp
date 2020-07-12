#include <forward_list>
#include "../catch.hpp"
#include "../../src/Matchers/PlusMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("PlusMatcher matches one or more elements")
{
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
        REQUIRE(*(pa.match(input, 0)) == Result(0, 0));
        REQUIRE(pa.next() == NULL);
    }

    SECTION("Result of matching the second element from the beginning")
    {
        REQUIRE(pb.match(input, 0) == NULL);
    }

    SECTION("Result of matching the second element from the element")
    {
        REQUIRE(*(pb.match(input, 1)) == Result(1, 1));
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
        REQUIRE(*(pc.match(input, 2)) == Result(2, 3));
        REQUIRE(*(pc.next()) == Result(2, 2));
        REQUIRE(pc.next() == NULL);
    }

    SECTION("Result of matching separated elements from beginning")
    {
        REQUIRE(pd.match(input, 0) == NULL);
    }

    SECTION("Result of matching separated elements from position")
    {
        REQUIRE(*(pd.match(input, 4)) == Result(4, 4));
        REQUIRE(pd.next() == NULL);
    }
}
