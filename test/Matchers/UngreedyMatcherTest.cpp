#include "../catch.hpp"
#include "../../src/Matchers/StarMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchers/UngreedyMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"
#include "../../src/Result.hpp"

TEST_CASE("UngreedyMatcher matches with as few elements as possible")
{
    Result *r;
    StringMatchable a("a");
    StringMatcher ma("a");
    StarMatcher sa(&ma);
    UngreedyMatcher m(&sa);
    vector<MatchableInterface *> input{&a, &a, &a};

    SECTION("Result an element from the beginning")
    {
        REQUIRE(*(r = m.match(input, 0)) == Result(-1, -1));
        delete r;
        REQUIRE(*(m.next()) == Result(0, 0));
        REQUIRE(*(m.next()) == Result(0, 1));
        REQUIRE(*(m.next()) == Result(0, 2));
        REQUIRE(m.next() == NULL);
    }

    SECTION("Result of matching the second element")
    {
        REQUIRE(*(r = m.match(input, 1)) == Result(0, 0));
        delete r;
        REQUIRE(*(m.next()) == Result(1, 1));
        REQUIRE(*(m.next()) == Result(1, 2));
        REQUIRE(m.next() == NULL);
    }

    SECTION("Not matches sequence at the end")
    {
        REQUIRE(m.match(input, input.size()) == NULL);
        REQUIRE(m.next() == NULL);
    }

    SECTION("Not matches sequence after end")
    {
        REQUIRE(m.match(input, input.size() + 1) == NULL);
        REQUIRE(m.next() == NULL);
    }
}
