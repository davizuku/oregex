#include "catch.hpp"
#include <iostream>
#include <string>
#include <regex>
#include "../src/Oregex.hpp"
#include "../src/Matchers/StringMatcher.hpp"
#include "../src/Matchers/StartMatcher.hpp"
#include "../src/Matchers/EndMatcher.hpp"
#include "../src/Matchers/StarMatcher.hpp"
#include "../src/Matchers/RangeMatcher.hpp"
#include "../src/Matchers/ExactlyMatcher.hpp"
#include "../src/Matchers/GroupMatcher.hpp"
#include "../src/Matchers/NamedGroupMatcher.hpp"
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
    StringMatchable a("a"), b("b"), c("c"), d("d"), e("e");
    StringMatcher m1("a"), m2("b"), m3("x"), m4("c"), m5("d"), m6("e");
    StarMatcher s1(&m1), s2(&m2), s3(&m3), s4(&m4), s5(&m5);

    auto testProvider = vector<TestArgs>{
        TestArgs{
            "String 'a' into regex '/a/' (3 steps)",
            "a",
            regex("a"),
            vector<MatchableInterface *>{&a},
            Oregex(vector<MatcherInterface *>{&m1})
        },
        TestArgs{
            "String 'b' into regex '/a/' (no match)",
            "b",
            regex("a"),
            vector<MatchableInterface *>{&b},
            Oregex(vector<MatcherInterface *>{&m1})
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
                    new GroupMatcher(vector<MatcherInterface *>{&m1, &m2, &m4})
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
                    new GroupMatcher(vector<MatcherInterface *>{&m1, &m2, &m4}),
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
                &m1,
                &m2,
                new GroupMatcher(vector<MatcherInterface *>{&s4}),
                &m5,
                new GroupMatcher(vector<MatcherInterface *>{
                    new StarMatcher(
                        new GroupMatcher(vector<MatcherInterface *>{&m6, &m5})
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
                &s4,
                &m5,
                new StarMatcher(new StringMatcher("ed"))
            })
        },
        TestArgs{
            "String 'aaaaaaacaaaaaacb' into regex '/a*c*b/' (28 steps)",
            "aaaaaaacaaaaaacb",
            regex("a*c*b"),
            vector<MatchableInterface *>{&a, &a, &a, &a, &a, &a, &a, &c, &a, &a, &a, &a, &a, &a, &c, &b},
            Oregex(vector<MatcherInterface *>{&s1, &s4, &m2})
        },
        TestArgs{
            "String 'aaacaaac' into regex '/a*c*b/' (no match)",
            "aaacaaac",
            regex("a*c*b"),
            vector<MatchableInterface *>{&a, &a, &a, &c, &a, &a, &a, &c},
            Oregex(vector<MatcherInterface *>{&s1, &s4, &m2})
        },
        TestArgs{
            "String 'aababcabcd' into regex '/(a*b*c*)*/' (44 steps)",
            "aababcabcd",
            regex("(a*b*c*)*"),
            vector<MatchableInterface *>{&a, &a, &b, &a, &b, &c, &a, &b, &c, &d},
            Oregex(vector<MatcherInterface *>{
                new StarMatcher(new GroupMatcher(vector<MatcherInterface *>{&s1, &s2, &s4,}))
            })
        },
        TestArgs{
            "String 'aababcabcd' into regex '/((a*)(b*)(c*))*/' (92 steps)",
            "aababcabcd",
            regex("((a*)(b*)(c*))*"),
            vector<MatchableInterface *>{&a, &a, &b, &a, &b, &c, &a, &b, &c, &d},
            Oregex(vector<MatcherInterface *>{
                new StarMatcher(new GroupMatcher(vector<MatcherInterface *>{
                    new GroupMatcher(vector<MatcherInterface *>{&s1}),
                    new GroupMatcher(vector<MatcherInterface *>{&s2}),
                    new GroupMatcher(vector<MatcherInterface *>{&s4}),
                }))
            })
        },
        TestArgs{
            "String 'aababcabcd' into regex '/(a*b*ec*)*/' (110 steps)",
            "aababcabcd",
            regex("(a*b*ec*)*"),
            vector<MatchableInterface *>{&a, &a, &b, &a, &b, &c, &a, &b, &c, &d},
            Oregex(vector<MatcherInterface *>{
                new StarMatcher(new GroupMatcher(vector<MatcherInterface *>{&s1, &s2, &m6, &s4,}))
            })
        },
        TestArgs{
            "String 'abccded' into regex '/^ded/' (no match)",
            "abccded",
            regex("^ded"),
            vector<MatchableInterface *>{&a, &b, &c, &c, &d, &e, &d},
            Oregex(vector<MatcherInterface *>{new StartMatcher(), &m5, &m6, &m5})
        },
        TestArgs{
            "String 'abccded' into regex '/^abc/' (6 steps)",
            "abccded",
            regex("^abc"),
            vector<MatchableInterface *>{&a, &b, &c, &c, &d, &e, &d},
            Oregex(vector<MatcherInterface *>{new StartMatcher(), &m1, &m2, &m4})
        },
        TestArgs{
            "String 'abccded' into regex '/ded$/' (5 steps)",
            "abccded",
            regex("ded$"),
            vector<MatchableInterface *>{&a, &b, &c, &c, &d, &e, &d},
            Oregex(vector<MatcherInterface *>{&m5, &m6, &m5, new EndMatcher()})
        },
        TestArgs{
            "String 'abccded' into regex '/abc$/' (no match)",
            "abccded",
            regex("abc$"),
            vector<MatchableInterface *>{&a, &b, &c, &c, &d, &e, &d},
            Oregex(vector<MatcherInterface *>{&m1, &m2, &m4, new EndMatcher()})
        },
        TestArgs{
            "String 'aaaaa' into regex '/a{0,5}a{1,5}a{2,5}/' (12 steps)",
            "aaaaa",
            regex("a{0,5}a{1,5}a{2,5}"),
            vector<MatchableInterface *>{&a, &a, &a, &a, &a},
            Oregex(vector<MatcherInterface *>{
                new RangeMatcher(&m1, 0, 5),
                new RangeMatcher(&m1, 1, 5),
                new RangeMatcher(&m1, 2, 5),
            })
        },
        TestArgs{
            "String 'abababc' into regex '/(ab){2,3}(abc)/' (18 steps)",
            "abababc",
            regex("(ab){2,3}(abc)"),
            vector<MatchableInterface *>{&a, &b, &a, &b, &a, &b, &c},
            Oregex(vector<MatcherInterface *>{
                new RangeMatcher(new GroupMatcher(vector<MatcherInterface *>{&m1, &m2}), 2, 3),
                new GroupMatcher(vector<MatcherInterface *>{&m1, &m2, &m4}),
            })
        },
        TestArgs{
            "String 'aaabc' into regex '/(a{1,2}){2}(abc)/' (19 steps)",
            "aaabc",
            regex("(a{1,2}){2}(abc)"),
            vector<MatchableInterface *>{&a, &a, &a, &b, &c},
            Oregex(vector<MatcherInterface *>{
                new ExactlyMatcher(new RangeMatcher(&m1, 1, 2), 2),
                new GroupMatcher(vector<MatcherInterface *>{&m1, &m2, &m4}),
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
