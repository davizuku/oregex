#include "catch.hpp"
#include <vector>
#include "../src/Result.hpp"
#include "../src/Oregex.hpp"
#include "../src/Matchers/StringMatcher.hpp"
#include "../src/Matchers/StarMatcher.hpp"
#include "../src/Matchers/GroupMatcher.hpp"
#include "../src/Matchers/NamedGroupMatcher.hpp"
#include "../src/Matchers/MatcherInterface.hpp"
#include "../src/Matchables/StringMatchable.hpp"
#include "../src/Matchables/MatchableInterface.hpp"

TEST_CASE("Oregex is built from Matchers and is executed on Matchables")
{
    StringMatchable a("a"), b("b"), c("c"), d("d"), e("e");
    StringMatcher m1("a"), m2("b"), m3("x"), m4("c"), m5("d"), m6("e");
    StarMatcher s1(&m1), s2(&m2), s3(&m3), s4(&m4), s5(&m5);
    vector<MatchableInterface *> input{&a, &b, &c, &c, &d, &e, &d};

    SECTION("Matches sequence in the beginning (/abc/ -> abccded)")
    {
        Oregex r(vector<MatcherInterface *>{&m1, &m2, &m4});
        REQUIRE(r.match(input) == true);
    }

    SECTION("Matches sequence in the middle (/c*/ -> abccded)")
    {
        Oregex r(vector<MatcherInterface *>{&s4});
        REQUIRE(r.match(input) == true);
    }

    SECTION("Matches sequence in the end (/ded/ -> abccded)")
    {
        Oregex r(vector<MatcherInterface *>{&m5, &m6, &m5});
        REQUIRE(r.match(input) == true);
    }

    SECTION("Not matches sequence (/x/ -> abccded)")
    {
        Oregex r(vector<MatcherInterface *>{&m3});
        REQUIRE(r.match(input) == false);
    }

    SECTION("Nested outputs /(?<all>ab(?<some>c*)d(?<end>ed)*)/ -> abccded")
    {
        map<string, forward_list<MatchableInterface *>> outputs, expected;
        expected["all"] = forward_list<MatchableInterface *>{&a, &b, &c, &c, &d, &e, &d};
        expected["some"] = forward_list<MatchableInterface *>{&c, &c};
        expected["end"] = forward_list<MatchableInterface *>{&e, &d};
        Oregex r(vector<MatcherInterface *>{
            new NamedGroupMatcher(
                "all",
                new GroupMatcher(vector<MatcherInterface *>{
                    &m1,
                    &m2,
                    new NamedGroupMatcher("some", &s4),
                    &m5,
                    new NamedGroupMatcher(
                        "end",
                        new StarMatcher(
                            new GroupMatcher(vector<MatcherInterface *>{&m6, &m5})
                        )
                    )
                })
            )
        });
        REQUIRE(r.match(input, outputs) == true);
        REQUIRE(outputs == expected);
    }
}
