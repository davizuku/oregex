#include "catch.hpp"
#include <vector>
#include "../src/Result.hpp"
#include "../src/Oregex.hpp"
#include "../src/Matchers/AgainMatcher.hpp"
#include "../src/Matchers/StringMatcher.hpp"
#include "../src/Matchers/StartMatcher.hpp"
#include "../src/Matchers/EndMatcher.hpp"
#include "../src/Matchers/StarMatcher.hpp"
#include "../src/Matchers/RangeMatcher.hpp"
#include "../src/Matchers/ExactlyMatcher.hpp"
#include "../src/Matchers/GroupMatcher.hpp"
#include "../src/Matchers/NamedGroupMatcher.hpp"
#include "../src/Matchers/OrMatcher.hpp"
#include "../src/Matchers/MatcherInterface.hpp"
#include "../src/Matchables/StringMatchable.hpp"
#include "../src/Matchables/MatchableInterface.hpp"

TEST_CASE("Oregex is built from Matchers and is executed on Matchables")
{
    StringMatchable a("a"), b("b"), c("c"), d("d"), e("e"), x("x");
    StringMatcher ma("a"), mb("b"), mx("x"), mc("c"), md("d"), me("e");
    StarMatcher sa(&ma), sb(&mb), sx(&mx), sc(&mc), sd(&md);
    vector<MatchableInterface *> input{&a, &b, &c, &c, &d, &e, &d};

    SECTION("Matches sequence in the beginning (/abc/ -> abccded)")
    {
        Oregex r(vector<MatcherInterface *>{&ma, &mb, &mc});
        REQUIRE(r.match(input) == true);
    }

    SECTION("Matches sequence in the middle (/c*/ -> abccded)")
    {
        Oregex r(vector<MatcherInterface *>{&sc});
        REQUIRE(r.match(input) == true);
    }

    SECTION("Matches exactly 2 in the middle (/c{2}/ -> abccded)")
    {
        Oregex r(vector<MatcherInterface *>{new ExactlyMatcher(&mc, 2)});
        REQUIRE(r.match(input) == true);
    }

    SECTION("Matches exactly 3 times a group (/(abc){3}/ -> abcabcabc)")
    {
        Oregex r(vector<MatcherInterface *>{
            new ExactlyMatcher(
                new GroupMatcher(vector<MatcherInterface *>{&ma, &mb, &mc}),
                3
            )
        });
        vector<MatchableInterface *> in_abc3{&a, &b, &c, &a, &b, &c, &a, &b, &c};
        REQUIRE(r.match(in_abc3) == true);
    }

    SECTION("Match needs to backtrack on a RangeMatcher results (/(a{1,2}){2}(abc)/ -> aaabc)")
    {
        input = vector<MatchableInterface *>{&a, &a, &a, &b, &c};
        Oregex r(vector<MatcherInterface *>{
            new ExactlyMatcher(new RangeMatcher(&ma, 1, 2), 2),
            new GroupMatcher(vector<MatcherInterface *>{&ma, &mb, &mc}),
        });
        REQUIRE(r.match(input) == true);
    }

    SECTION("Not matches exactly 3 (/a{3}a/ -> aaa)")
    {
        Oregex r(vector<MatcherInterface *>{new RangeMatcher(&ma, 3, 3), &ma});
        vector<MatchableInterface *> in_aaaa{&a, &a, &a};
        REQUIRE(r.match(in_aaaa) == false);
    }

    SECTION("Matches sequence in the end (/ded/ -> abccded)")
    {
        Oregex r(vector<MatcherInterface *>{&md, &me, &md});
        REQUIRE(r.match(input) == true);
    }

    SECTION("Matches sequence in the end (/ded$/ -> abccded)")
    {
        Oregex r(vector<MatcherInterface *>{&md, &me, &md, new EndMatcher()});
        REQUIRE(r.match(input) == true);
    }

    SECTION("Not matches sequence in the beginning (/^ded/ -> abccded)")
    {
        Oregex r(vector<MatcherInterface *>{new StartMatcher(), &md, &me, &md});
        REQUIRE(r.match(input) == false);
    }

    SECTION("Not matches sequence in the end (/abc$/ -> abccded)")
    {
        Oregex r(vector<MatcherInterface *>{&ma, &mb, &mc, new EndMatcher()});
        REQUIRE(r.match(input) == false);
    }

    SECTION("Not matches sequence (/x/ -> abccded)")
    {
        Oregex r(vector<MatcherInterface *>{&mx});
        REQUIRE(r.match(input) == false);
    }

    SECTION("Nested outputs /(?<all>ab(?<some>c*)d(?<end>ed)*)/ -> abccded")
    {
        unordered_map<string, forward_list<MatchableInterface *>> outputs, expected;
        expected["all"] = forward_list<MatchableInterface *>{&a, &b, &c, &c, &d, &e, &d};
        expected["some"] = forward_list<MatchableInterface *>{&c, &c};
        expected["end"] = forward_list<MatchableInterface *>{&e, &d};
        Oregex r(vector<MatcherInterface *>{
            new NamedGroupMatcher(
                "all",
                new GroupMatcher(vector<MatcherInterface *>{
                    &ma,
                    &mb,
                    new NamedGroupMatcher("some", &sc),
                    &md,
                    new NamedGroupMatcher(
                        "end",
                        new StarMatcher(
                            new GroupMatcher(vector<MatcherInterface *>{&me, &md})
                        )
                    )
                })
            )
        });
        REQUIRE(r.match(input, outputs) == true);
        REQUIRE(outputs == expected);
    }

    SECTION("Maches discarding second element in or (/(a*|abc)(abc)*d/ -> abcd)")
    {
        Oregex r(vector<MatcherInterface *>{
            new OrMatcher(vector<MatcherInterface *>{
                &sa,
                new GroupMatcher(vector<MatcherInterface *>{&ma, &mb, &mc}),
            }),
            new StarMatcher(
                new GroupMatcher(vector<MatcherInterface *>{&ma, &mb, &mc})
            ),
            &md
        });
        vector<MatchableInterface *> input{&a, &b, &c, &d};
        REQUIRE(r.match(input) == true);
    }

    SECTION("Matches using previous results (/(?<first>abc)x(\k<first>)/ -> abcxabc)")
    {
        Oregex r(vector<MatcherInterface *>{
            new NamedGroupMatcher("first", new GroupMatcher(vector<MatcherInterface *>{&ma, &mb, &mc})),
            &mx,
            new AgainMatcher("first"),
        });
        vector<MatchableInterface *> input{&a, &b, &c, &x, &a, &b, &c};
        REQUIRE(r.match(input) == true);
    }
}
