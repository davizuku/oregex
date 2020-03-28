#include "catch.hpp"
#include "../src/Result.hpp"
#include "../src/Matchables/StringMatchable.hpp"
#include "../src/Matchables/MatchableInterface.hpp"

StringMatchable a("a"), b("b"), c("c");

TEST_CASE("Results contain a pointer to the first and last matched index and outputs")
{
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

TEST_CASE("Results must compare all their properties for equality")
{
    SECTION("Comparing first indices")
    {
        REQUIRE(Result(1, 5) == Result(1, 5));
        REQUIRE_FALSE(Result(2, 5) == Result(1, 5));
        REQUIRE(Result(2, 5) != Result(1, 5));
        REQUIRE_FALSE(Result(2, 5) != Result(2, 5));
    }

    SECTION("Comparing last indices")
    {
        REQUIRE(Result(0, 1) == Result(0, 1));
        REQUIRE_FALSE(Result(0, 2) == Result(0, 1));
        REQUIRE(Result(0, 2) != Result(0, 1));
        REQUIRE_FALSE(Result(0, 2) != Result(0, 2));
    }

    SECTION("Comparing outputs")
    {
        unordered_map<string, forward_list<MatchableInterface *>> o1, o2;
        o1["a"] = forward_list<MatchableInterface *>{&a, &b};
        o2["b"] = forward_list<MatchableInterface *>{&c};
        REQUIRE(Result(0, 1, o1) == Result(0, 1, o1));
        REQUIRE_FALSE(Result(0, 1, o1) == Result(0, 1, o2));
        REQUIRE(Result(0, 1, o1) != Result(0, 1, o2));
        REQUIRE_FALSE(Result(0, 1, o1) != Result(0, 1, o1));
    }
}
