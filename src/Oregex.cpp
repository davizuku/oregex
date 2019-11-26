#include "Oregex.hpp"
#include "Result.hpp"
#include <forward_list>
#include <iostream>

using namespace std;

Oregex::Oregex(const vector<MatcherInterface *> &m)
{
    matchers = m;
}

Oregex::~Oregex()
{
}

bool recursive_match(
    vector<MatcherInterface *> &matchers,
    int matcherIndex,
    vector<MatchableInterface *> &matchables,
    int matchableIndex,
    forward_list<Result> &previousResults
) {
    if (matcherIndex >= matchers.size()) {
        return true;
    }
    if (matchableIndex >= matchables.size()) {
        return false;
    }
    forward_list<Result> results = matchers[matcherIndex]->match(
        matchables,
        matchableIndex,
        previousResults);
    if (results.empty()) {
        return recursive_match(
            matchers,
            matcherIndex,
            matchables,
            matchableIndex + 1,
            results
        );
    }
    for (Result& r: results) {
        bool isSubmatch = recursive_match(
            matchers,
            matcherIndex + 1,
            matchables,
            r.getLastMatchedIndex() + 1,
            results
        );
        if (isSubmatch) {
            return true;
        }
    }
    return false;
}

bool Oregex::match(vector<MatchableInterface *> &matchables)
{
    forward_list<Result> previousResults;
    return recursive_match(matchers, 0, matchables, 0, previousResults);
}
