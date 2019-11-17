#include <vector>
#include <map>
#include <string>
#include "catch.hpp"
#include "../src/Result.hpp"
#include "../src/Matchables/StringMatchable.hpp"
#include "../src/Matchables/MatchableInterface.hpp"

using namespace std;

TEST_CASE("Results contain two lists of matched and not matched elements and outputs")
{
    Result res;
    StringMatchable a("a"), b("b"), c("c"), d("d"), e("e"), f("f");
    vector<MatchableInterface*> matched{&a, &b, &c}, notMatched {&d, &e,&f};
    map<string, vector<MatchableInterface*> > outputs;
    outputs["first"] = vector<MatchableInterface*>{&a, &b};
    outputs["second"] = vector<MatchableInterface*>{&c};
    res.setMatched(matched);
    res.setNotMatched(notMatched);
    res.setOutputs(outputs);
    REQUIRE(res.getMatched() == matched);
    REQUIRE(res.getNotMatched() == notMatched);
    REQUIRE(res.getOutputs() == outputs);
}
