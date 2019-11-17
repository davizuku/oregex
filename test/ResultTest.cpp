#include <forward_list>
#include <map>
#include <string>
#include "catch.hpp"
#include "../src/Result.hpp"
#include "../src/Matchables/StringMatchable.hpp"
#include "../src/Matchables/MatchableInterface.hpp"

using namespace std;

TEST_CASE("Results contain two lists of consumed and pending elements and outputs")
{
    Result res;
    StringMatchable a("a"), b("b"), c("c"), d("d"), e("e"), f("f");
    forward_list<MatchableInterface*> consumed{&a, &b, &c}, pending {&d, &e,&f};
    map<string, forward_list<MatchableInterface*> > outputs;
    outputs["first"] = forward_list<MatchableInterface*>{&a, &b};
    outputs["second"] = forward_list<MatchableInterface*>{&c};
    res.setConsumed(consumed);
    res.setPending(pending);
    res.setOutputs(outputs);
    REQUIRE(res.getConsumed() == consumed);
    REQUIRE(res.getPending() == pending);
    REQUIRE(res.getOutputs() == outputs);
}
