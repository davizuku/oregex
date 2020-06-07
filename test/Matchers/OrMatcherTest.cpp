#include "../catch.hpp"
#include "../../src/Matchables/StringMatchable.hpp"
#include "../../src/Matchers/OrMatcher.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Result.hpp"

TEST_CASE("OrMatcher matches any of the specified submatchers in order")
{
    StringMatchable a("a"), b("b"), c("c");
    StringMatcher ma("a"), mb("b"), mc("c");
    vector<MatchableInterface *> input{&a, &b, &c, &c};

    SECTION("Not matches sequence at the end")
    {
        OrMatcher m(vector<MatcherInterface*>{&ma, &mb, &mc});
        REQUIRE(m.match(input, input.size()) == NULL);
        REQUIRE(m.next() == NULL);
    }
}
