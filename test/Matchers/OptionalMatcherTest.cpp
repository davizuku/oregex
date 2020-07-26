#include <forward_list>
#include "../catch.hpp"
#include "../../src/Matchers/OptionalMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("OptionalMatcher matches zero or one element")
{
    Result *r;
    StringMatchable a("a"), b("b");
    StringMatcher ma("a"), mb("b");
    OptionalMatcher m(&ma);
    vector<MatchableInterface *> input{&a, &b};

    SECTION("Not matches sequence at the end")
    {
        REQUIRE(m.match(input, input.size()) == NULL);
    }

    SECTION("Not matches sequence after end")
    {
        REQUIRE(m.match(input, input.size() + 1) == NULL);
    }

    SECTION("Result of matching elements from the beginning")
    {
        REQUIRE(*(r = m.match(input, 0)) == Result(0, 0));
        delete r;
        REQUIRE(*(m.next()) == Result(-1, -1));
        REQUIRE(m.next() == NULL);
    }

    SECTION("Result of not matching any element from the beginning")
    {
        m = OptionalMatcher(&mb);
        REQUIRE(*(r = m.match(input, 0)) == Result(-1, -1));
        delete r;
        REQUIRE(m.next() == NULL);
    }
}
