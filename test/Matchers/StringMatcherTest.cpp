#include "../catch.hpp"
#include "../../src/Matchers/StringMatcher.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("StringMatcher matches only with same strings")
{
    StringMatchable a("a"), b("b"), c("c"), d("d");
    StringMatcher m1("a"), m2("b"), m3("x");

    vector<MatchableInterface *>
        input{&a, &b, &c},
        expectedMatchedM1{&a},
        expectedNotMatchedM1{&b, &c},
        expectedMatchedM2{&a, &b},
        expectedNotMatchedM2{&c},
        expectedMatchedM3{&a, &b, &c},
        expectedNotMatchedM3{};
    map<string, vector<MatchableInterface*> > expectedOutputs;

    Result r1 = m1.match(input);
    Result r2 = m2.match(input);
    Result r3 = m3.match(input);

    REQUIRE(r1.getMatched() == expectedMatchedM1);
    REQUIRE(r1.getNotMatched() == expectedNotMatchedM1);
    REQUIRE(r1.getOutputs() == expectedOutputs);
    REQUIRE(r2.getMatched() == expectedMatchedM2);
    REQUIRE(r2.getNotMatched() == expectedNotMatchedM2);
    REQUIRE(r2.getOutputs() == expectedOutputs);
    REQUIRE(r3.getMatched() == expectedMatchedM3);
    REQUIRE(r3.getNotMatched() == expectedNotMatchedM3);
    REQUIRE(r3.getOutputs() == expectedOutputs);
}
