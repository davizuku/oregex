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
        expectedMatchedM1{&a},
        expectedNotMatchedM1{&b, &c},
        expectedMatchedM2{&a, &b},
        expectedNotMatchedM2{&c},
        expectedMatchedM3{&a, &b, &c},
        expectedNotMatchedM3{};
    map<string, forward_list<MatchableInterface*> > expectedOutputs;

    Result r1 = m1.match(input);
    REQUIRE(r1.getConsumed() == expectedMatchedM1);
    REQUIRE(r1.getPending() == expectedNotMatchedM1);
    REQUIRE(r1.getOutputs() == expectedOutputs);

    Result r2 = m2.match(input);
    REQUIRE(r2.getConsumed() == expectedMatchedM2);
    REQUIRE(r2.getPending() == expectedNotMatchedM2);
    REQUIRE(r2.getOutputs() == expectedOutputs);

    Result r3 = m3.match(input);
    REQUIRE(r3.getConsumed() == expectedMatchedM3);
    REQUIRE(r3.getPending() == expectedNotMatchedM3);
    REQUIRE(r3.getOutputs() == expectedOutputs);
}
