#include "../catch.hpp"
#include "../../src/Matchables/StringMatchable.hpp"

TEST_CASE("StringMatchable stores string as value")
{
    StringMatchable sm1("hello");
    REQUIRE(sm1.getValue() == "hello");
}
