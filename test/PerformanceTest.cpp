#include "catch.hpp"
#include <iostream>
#include <string>
#include <regex>
#include "../src/Oregex.hpp"
#include "../src/Matchers/StringMatcher.hpp"
#include "../src/Matchers/StarMatcher.hpp"
#include "../src/Matchers/GroupMatcher.hpp"
#include "../src/Matchers/NamedGroupMatcher.hpp"
#include "../src/Matchers/MatcherInterface.hpp"
#include "../src/Matchables/StringMatchable.hpp"
#include "../src/Matchables/MatchableInterface.hpp"

using namespace std;

TEST_CASE("Given the same set of strings how much faster is regex module")
{
    string strInput = "abccded";
    regex strRegex("ab(c*)d((ed)*)");
    StringMatchable a("a"), b("b"), c("c"), d("d"), e("e");
    StringMatcher m1("a"), m2("b"), m3("x"), m4("c"), m5("d"), m6("e");
    StarMatcher s1(&m1), s2(&m2), s3(&m3), s4(&m4), s5(&m5);
    vector<MatchableInterface *> matchableInput{&a, &b, &c, &c, &d, &e, &d};
    Oregex oRegex(vector<MatcherInterface *>{
        &m1,
        &m2,
        new GroupMatcher(vector<MatcherInterface *>{&s4}),
        &m5,
        new GroupMatcher(vector<MatcherInterface *>{
            new StarMatcher(
                new GroupMatcher(vector<MatcherInterface *>{&m6, &m5})
            )
        })
    });
    float tRegex = 0, tOregex = 0;
    unsigned int nIterations = 100;
    for (unsigned i = 0; i < nIterations; ++i) {
        clock_t t0 = clock();
        bool r1 = regex_match(strInput, strRegex);
        clock_t t1 = clock();
        bool r2 = oRegex.match(matchableInput);
        clock_t t2 = clock();
        REQUIRE(r1 == r2);
        tRegex += (float)(t1 - t0) / CLOCKS_PER_SEC;
        tOregex += (float)(t2 - t1) / CLOCKS_PER_SEC;
    }
    cout << "Average time std regex: " << tRegex / nIterations << endl;
    cout << "Average time oregex: " << tOregex / nIterations << endl;
}
