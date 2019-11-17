#include <forward_list>
#include "../catch.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("StringMatcher matches only with same strings")
{
    StringMatchable a("a"), b("b"), c("c"), d("d");
    StringMatcher m1("a"), m2("b"), m3("x");
    forward_list<MatchableInterface*>
        input{&a, &b, &c},
        expectedConsumedM1{&a},
        expectedPendingM1{&b, &c},
        expectedConsumedM2{&a, &b},
        expectedPendingM2{&c},
        expectedConsumedM3{&a, &b, &c},
        expectedPendingM3{};
    map<string, forward_list<MatchableInterface*> > expectedOutputs;

    Result r1 = m1.match(input).front();
    REQUIRE(r1.getConsumed() == expectedConsumedM1);
    REQUIRE(r1.getPending() == expectedPendingM1);
    REQUIRE(r1.getOutputs() == expectedOutputs);

    Result r2 = m2.match(input).front();
    REQUIRE(r2.getConsumed() == expectedConsumedM2);
    REQUIRE(r2.getPending() == expectedPendingM2);
    REQUIRE(r2.getOutputs() == expectedOutputs);

    Result r3 = m3.match(input).front();
    REQUIRE(r3.getConsumed() == expectedConsumedM3);
    REQUIRE(r3.getPending() == expectedPendingM3);
    REQUIRE(r3.getOutputs() == expectedOutputs);
}
