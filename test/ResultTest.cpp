#include "catch.hpp"
#include "../src/Result.hpp"
#include "../src/Matchables/StringMatchable.hpp"
#include "../src/Matchables/MatchableInterface.hpp"

TEST_CASE("Results contain a pointer to the first and last matched index and outputs")
{
    StringMatchable a("a"), b("b"), c("c");
    vector<MatchableInterface *> input{&a, &b, &c};
    unordered_map<string, forward_list<MatchableInterface *>> outputs;
    outputs["first"] = forward_list<MatchableInterface *>{&a, &b};
    outputs["second"] = forward_list<MatchableInterface *>{&c};

    SECTION("Setting iterator in constructor")
    {
        Result res(0, 1);
        REQUIRE(res.getFirstMatchedIndex() == 0);
        REQUIRE(res.getLastMatchedIndex() == 1);
    }

    SECTION("Setting outputs in setter")
    {
        Result res(0, 1);
        res.setOutputs(outputs);
        REQUIRE(res.getOutputs() == outputs);
    }

    SECTION("Setting outputs in constructor")
    {
        Result res(0, 1, outputs);
        REQUIRE(res.getOutputs() == outputs);
    }
}
