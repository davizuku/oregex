#include "GroupMatcher.hpp"
#include <list>

GroupMatcher::GroupMatcher(const vector<MatcherInterface *> &m)
{
    matchers = m;
}

GroupMatcher::~GroupMatcher()
{
}

Result* GroupMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    auto copyPrevResults = previousResults;
    results = list<Result*>();
    recursiveMatch(
        0,
        matchables,
        start,
        copyPrevResults,
        NULL
    );
    resultIt = results.begin();
    return next();
}

Result* GroupMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* GroupMatcher::next()
{
    if (resultIt == results.end()) {
        return NULL;
    }
    Result* r = *resultIt;
    resultIt++;
    return r;
}

Result* mergeResults(Result* a, Result* b)
{
    if (a != NULL and b != NULL) {
        unordered_map<string, forward_list<MatchableInterface *>> outputs{a->getOutputs()};
        auto outB = b->getOutputs();
        outputs.insert(outB.begin(), outB.end());
        return new Result(
            -1,
            max(a->getLastMatchedIndex(), b->getLastMatchedIndex()),
            outputs
        );
    }
    return a == NULL ? b : a;
}

void GroupMatcher::recursiveMatch(
    size_t matcherIndex,
    const vector<MatchableInterface *> &matchables,
    size_t matchableIndex,
    forward_list<Result> &previousResults,
    Result* accResult
) {
    if (matcherIndex >= matchers.size() or
        matchableIndex >= matchables.size()
    ) {
        return;
    }
    Result* r = matchers[matcherIndex]->match(
        matchables,
        matchableIndex,
        previousResults
    );
    while (r != NULL) {
        previousResults.push_front(*r);
        Result* finalRes = mergeResults(accResult, r);
        if (matcherIndex == matchers.size() - 1) {
            results.push_back(finalRes);
        } else {
            recursiveMatch(
                matcherIndex + 1,
                matchables,
                r->getLastMatchedIndex() + 1,
                previousResults,
                finalRes
            );
        }
        previousResults.pop_front();
        r = matchers[matcherIndex]->next();
    }
}
