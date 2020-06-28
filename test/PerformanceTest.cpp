#include "catch.hpp"
#include <iostream>
#include <string>
#include <regex>
#include "../src/Oregex.hpp"
#include "../src/Matchers/AgainMatcher.hpp"
#include "../src/Matchers/AnyMatcher.hpp"
#include "../src/Matchers/StringMatcher.hpp"
#include "../src/Matchers/StartMatcher.hpp"
#include "../src/Matchers/EndMatcher.hpp"
#include "../src/Matchers/ExceptMatcher.hpp"
#include "../src/Matchers/StarMatcher.hpp"
#include "../src/Matchers/RangeMatcher.hpp"
#include "../src/Matchers/ExactlyMatcher.hpp"
#include "../src/Matchers/GroupMatcher.hpp"
#include "../src/Matchers/NamedGroupMatcher.hpp"
#include "../src/Matchers/OrMatcher.hpp"
#include "../src/Matchers/PositiveLookAheadMatcher.hpp"
#include "../src/Matchers/MatcherInterface.hpp"
#include "../src/Matchables/StringMatchable.hpp"
#include "../src/Matchables/MatchableInterface.hpp"

using namespace std;

struct TestArgs
{
    string name;
    string strInput;
    regex strRegex;
    vector<MatchableInterface *> oInput;
    Oregex oRegex;
};

TEST_CASE("Given the same set of strings how much faster is regex module")
{
    StringMatchable a("a"), b("b"), c("c"), d("d"), e("e"), x("x");
    StringMatcher ma("a"), mb("b"), mx("x"), mc("c"), md("d"), me("e");
    StarMatcher sa(&ma), sb(&mb), sx(&mx), sc(&mc), sd(&md);

    auto testProvider = vector<TestArgs>{
        TestArgs{
            "String 'a' into regex '/a/' (3 steps)",
            "a",
            regex("a"),
            vector<MatchableInterface *>{&a},
            Oregex(vector<MatcherInterface *>{&ma})
        },
        TestArgs{
            "String 'b' into regex '/a/' (no match)",
            "b",
            regex("a"),
            vector<MatchableInterface *>{&b},
            Oregex(vector<MatcherInterface *>{&ma})
        },
        TestArgs{
            "String 'abcçdefghijklmnñopqrstuvwxyz0123456789' into literal regex (39 steps)",
            "abcçdefghijklmnñopqrstuvwxyz0123456789",
            regex("abcçdefghijklmnñopqrstuvwxyz0123456789"),
            vector<MatchableInterface *>{new StringMatchable("abcçdefghijklmnñopqrstuvwxyz0123456789")},
            Oregex(vector<MatcherInterface *>{new StringMatcher("abcçdefghijklmnñopqrstuvwxyz0123456789")})
        },
        TestArgs{
            "String 'abcabcabc' into regex '/(abc)*/ naive' (25 steps)",
            "abcabcabc",
            regex("(abc)*"),
            vector<MatchableInterface *>{&a, &b, &c, &a, &b, &c, &a, &b, &c},
            Oregex(vector<MatcherInterface *>{
                new StarMatcher(
                    new GroupMatcher(vector<MatcherInterface *>{&ma, &mb, &mc})
                )
            })
        },
        TestArgs{
            "String 'abcabcabc' into regex '/(abc){3}/' (12 steps)",
            "abcabcabc",
            regex("(abc){3}"),
            vector<MatchableInterface *>{&a, &b, &c, &a, &b, &c, &a, &b, &c},
            Oregex(vector<MatcherInterface *>{
                new ExactlyMatcher(
                    new GroupMatcher(vector<MatcherInterface *>{&ma, &mb, &mc}),
                    3
                )
            })
        },
        TestArgs{
            "String 'abcabcabc' into regex '/(abc)*/ optimized' (25 steps)",
            "abcabcabc",
            regex("(abc)*"),
            vector<MatchableInterface *>{
                new StringMatchable("abc"),
                new StringMatchable("abc"),
                new StringMatchable("abc"),
            },
            Oregex(vector<MatcherInterface *>{
                new StarMatcher(new StringMatcher("abc"))
            })
        },
        TestArgs{
            "String 'abccded' into regex '/ab(c*)d((ed)*)/' naive (14 steps)",
            "abccded",
            regex("ab(c*)d((ed)*)"),
            vector<MatchableInterface *>{&a, &b, &c, &c, &d, &e, &d},
            Oregex(vector<MatcherInterface *>{
                &ma,
                &mb,
                new GroupMatcher(vector<MatcherInterface *>{&sc}),
                &md,
                new GroupMatcher(vector<MatcherInterface *>{
                    new StarMatcher(
                        new GroupMatcher(vector<MatcherInterface *>{&me, &md})
                    )
                })
            })
        },
        TestArgs{
            "String 'abccded' into regex '/ab(c*)d((ed)*)/' optimized (14 steps)",
            "abccded",
            regex("ab(c*)d((ed)*)"),
            vector<MatchableInterface *>{
                new StringMatchable("ab"),
                &c, &c, &d,
                new StringMatchable("ed"),
            },
            Oregex(vector<MatcherInterface *>{
                new StringMatcher("ab"),
                &sc,
                &md,
                new StarMatcher(new StringMatcher("ed"))
            })
        },
        TestArgs{
            "String 'aaaaaaacaaaaaacb' into regex '/a*c*b/' (28 steps)",
            "aaaaaaacaaaaaacb",
            regex("a*c*b"),
            vector<MatchableInterface *>{&a, &a, &a, &a, &a, &a, &a, &c, &a, &a, &a, &a, &a, &a, &c, &b},
            Oregex(vector<MatcherInterface *>{&sa, &sc, &mb})
        },
        TestArgs{
            "String 'aaacaaac' into regex '/a*c*b/' (no match)",
            "aaacaaac",
            regex("a*c*b"),
            vector<MatchableInterface *>{&a, &a, &a, &c, &a, &a, &a, &c},
            Oregex(vector<MatcherInterface *>{&sa, &sc, &mb})
        },
        TestArgs{
            "String 'aababcabcd' into regex '/(a*b*c*)*/' (44 steps)",
            "aababcabcd",
            regex("(a*b*c*)*"),
            vector<MatchableInterface *>{&a, &a, &b, &a, &b, &c, &a, &b, &c, &d},
            Oregex(vector<MatcherInterface *>{
                new StarMatcher(new GroupMatcher(vector<MatcherInterface *>{&sa, &sb, &sc,}))
            })
        },
        TestArgs{
            "String 'aababcabcd' into regex '/((a*)(b*)(c*))*/' (92 steps)",
            "aababcabcd",
            regex("((a*)(b*)(c*))*"),
            vector<MatchableInterface *>{&a, &a, &b, &a, &b, &c, &a, &b, &c, &d},
            Oregex(vector<MatcherInterface *>{
                new StarMatcher(new GroupMatcher(vector<MatcherInterface *>{
                    new GroupMatcher(vector<MatcherInterface *>{&sa}),
                    new GroupMatcher(vector<MatcherInterface *>{&sb}),
                    new GroupMatcher(vector<MatcherInterface *>{&sc}),
                }))
            })
        },
        TestArgs{
            "String 'aababcabcd' into regex '/(a*b*ec*)*/' (110 steps)",
            "aababcabcd",
            regex("(a*b*ec*)*"),
            vector<MatchableInterface *>{&a, &a, &b, &a, &b, &c, &a, &b, &c, &d},
            Oregex(vector<MatcherInterface *>{
                new StarMatcher(new GroupMatcher(vector<MatcherInterface *>{&sa, &sb, &me, &sc,}))
            })
        },
        TestArgs{
            "String 'abccded' into regex '/^ded/' (no match)",
            "abccded",
            regex("^ded"),
            vector<MatchableInterface *>{&a, &b, &c, &c, &d, &e, &d},
            Oregex(vector<MatcherInterface *>{new StartMatcher(), &md, &me, &md})
        },
        TestArgs{
            "String 'abccded' into regex '/^abc/' (6 steps)",
            "abccded",
            regex("^abc"),
            vector<MatchableInterface *>{&a, &b, &c, &c, &d, &e, &d},
            Oregex(vector<MatcherInterface *>{new StartMatcher(), &ma, &mb, &mc})
        },
        TestArgs{
            "String 'abccded' into regex '/ded$/' (5 steps)",
            "abccded",
            regex("ded$"),
            vector<MatchableInterface *>{&a, &b, &c, &c, &d, &e, &d},
            Oregex(vector<MatcherInterface *>{&md, &me, &md, new EndMatcher()})
        },
        TestArgs{
            "String 'abccded' into regex '/abc$/' (no match)",
            "abccded",
            regex("abc$"),
            vector<MatchableInterface *>{&a, &b, &c, &c, &d, &e, &d},
            Oregex(vector<MatcherInterface *>{&ma, &mb, &mc, new EndMatcher()})
        },
        TestArgs{
            "String 'aaaaa' into regex '/a{0,5}a{1,5}a{2,5}/' (12 steps)",
            "aaaaa",
            regex("a{0,5}a{1,5}a{2,5}"),
            vector<MatchableInterface *>{&a, &a, &a, &a, &a},
            Oregex(vector<MatcherInterface *>{
                new RangeMatcher(&ma, 0, 5),
                new RangeMatcher(&ma, 1, 5),
                new RangeMatcher(&ma, 2, 5),
            })
        },
        TestArgs{
            "String 'abababc' into regex '/(ab){2,3}(abc)/' (18 steps)",
            "abababc",
            regex("(ab){2,3}(abc)"),
            vector<MatchableInterface *>{&a, &b, &a, &b, &a, &b, &c},
            Oregex(vector<MatcherInterface *>{
                new RangeMatcher(new GroupMatcher(vector<MatcherInterface *>{&ma, &mb}), 2, 3),
                new GroupMatcher(vector<MatcherInterface *>{&ma, &mb, &mc}),
            })
        },
        TestArgs{
            "String 'aaabc' into regex '/(a{1,2}){2}(abc)/' (19 steps)",
            "aaabc",
            regex("(a{1,2}){2}(abc)"),
            vector<MatchableInterface *>{&a, &a, &a, &b, &c},
            Oregex(vector<MatcherInterface *>{
                new ExactlyMatcher(new RangeMatcher(&ma, 1, 2), 2),
                new GroupMatcher(vector<MatcherInterface *>{&ma, &mb, &mc}),
            })
        },
        TestArgs{
            "String 'abcd' into regex '/(a|abc)(bcc)*d/' (16 steps)",
            "abcd",
            regex("(a|abc)(bcc)*d"),
            vector<MatchableInterface *>{&a, &b, &c, &d},
            Oregex(vector<MatcherInterface *>{
                new OrMatcher(vector<MatcherInterface*>{
                    &ma,
                    new GroupMatcher(vector<MatcherInterface*>{&ma, &mb, &mc}),
                }),
                new StarMatcher(
                    new GroupMatcher(vector<MatcherInterface*>{&mb, &mc, &mc})
                ),
                &md
            })
        },
        TestArgs{
            "String 'a' into regex '/./' (3 steps)",
            "a",
            regex("."),
            vector<MatchableInterface *>{&a},
            Oregex(vector<MatcherInterface *>{new AnyMatcher()})
        },
        TestArgs{
            "String 'abcd' into regex '/a.*/' (4 steps)",
            "abcd",
            regex("a.*"),
            vector<MatchableInterface *>{&a, &b, &c, &d},
            Oregex(vector<MatcherInterface *>{
                &ma,
                new StarMatcher(new AnyMatcher()),
            })
        },
        TestArgs{
            "String 'aaaaxaaa' into regex '/(a*)x(\\k<1>)/' (14 steps)",
            "aaaaxaaa",
            regex("(a*)x(\\1)"),
            vector<MatchableInterface *>{&a, &a, &a, &a, &x, &a, &a, &a},
            Oregex(vector<MatcherInterface *>{
                new NamedGroupMatcher("1", &sa),
                &mx,
                new AgainMatcher("1"),
            })
        },
        TestArgs{
            "String 'abccde' into regex '/ab[^ab]+/' (11 steps)",
            "abccde",
            regex("ab[^ab]+"),
            vector<MatchableInterface *>{&a, &b, &c, &c, &d, &e},
            Oregex(vector<MatcherInterface *>{
                &ma,
                &mb,
                new RangeMatcher(
                    new ExceptMatcher(vector<MatcherInterface*>{&ma, &mb}),
                    1
                ),
            })
        },
        TestArgs{
            "String 'abab' into regex '/ab[^ab]+/' (6 steps)",
            "abab",
            regex("ab[^ab]+"),
            vector<MatchableInterface *>{&a, &b, &a, &b},
            Oregex(vector<MatcherInterface *>{
                &ma,
                &mb,
                new RangeMatcher(
                    new ExceptMatcher(vector<MatcherInterface*>{&ma, &mb}),
                    1
                ),
            })
        },
        TestArgs{
            "String 'abc' into regex '/a(?=bc)bc/' (8 steps)",
            "abc",
            regex("a(?=bc)bc"),
            vector<MatchableInterface *>{&a, &b, &c},
            Oregex(vector<MatcherInterface *>{
                &ma,
                new PositiveLookAheadMatcher(new GroupMatcher(vector<MatcherInterface*>{
                    &mb,
                    &mc
                })),
                &mb,
                &mc,
            })
        },
        TestArgs{
            "String 'acb' into regex '/a(?=bc)bc/' (3 steps)",
            "acb",
            regex("a(?=bc)bc"),
            vector<MatchableInterface *>{&a, &c, &b},
            Oregex(vector<MatcherInterface *>{
                &ma,
                new PositiveLookAheadMatcher(new GroupMatcher(vector<MatcherInterface*>{
                    &mb,
                    &mc
                })),
                &mb,
                &mc,
            })
        },
    };

    for (TestArgs &testCase : testProvider) {
        cout << endl << "Test: " << testCase.name << endl;
        float tRegex = 0, tOregex = 0;
        unsigned int nIterations = 1000;
        for (unsigned i = 0; i < nIterations; ++i) {
            clock_t t0 = clock();
            bool r1 = regex_search(testCase.strInput, testCase.strRegex);
            clock_t t1 = clock();
            bool r2 = testCase.oRegex.match(testCase.oInput);
            clock_t t2 = clock();
            REQUIRE(r1 == r2);
            tRegex += (float)(t1 - t0) / CLOCKS_PER_SEC;
            tOregex += (float)(t2 - t1) / CLOCKS_PER_SEC;
        }
        float avgRegex = tRegex / nIterations,
            avgOregex = tOregex / nIterations,
            ratio = avgOregex / avgRegex;
        cout << "\tAverage time std regex: " << avgRegex << "s" << endl;
        cout << "\tAverage time oregex: " << avgOregex << "s" << endl;
        cout << "\tRatio (oregex/std): ";
        if (ratio > 1.0) { // Red
            cout << "\033[1;31m";
        } else { // Green
            cout << "\033[1;32m";
        }
        cout << ratio*100 << "%";
        cout << "\033[0m" << endl; // Reset
    }
}
