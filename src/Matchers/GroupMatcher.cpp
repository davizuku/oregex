#include "GroupMatcher.hpp"

GroupMatcher::GroupMatcher(const vector<MatcherInterface *> &m)
{
    matchers = m;
    results = queue<Result>();
}

GroupMatcher::~GroupMatcher()
{
}

Result* GroupMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    if (matchers.empty()) {
        return NULL;
    }
    this->start = start;
    results = queue<Result>();
    auto copyPrevResults = previousResults;
    Result *r = matchers[0]->match(
        matchables,
        start,
        copyPrevResults
    );
    while (r != NULL) {
        Result curRes(*r);
        delete r;
        if (matchers.size() == 1) {
            results.push(curRes);
        } else {
            copyPrevResults.push_front(curRes);
            recursiveMatch(
                1,
                matchables,
                curRes.getLastMatchedIndex() + 1,
                copyPrevResults,
                curRes
            );
            copyPrevResults.pop_front();
        }
        r = matchers[0]->next();
    }
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
    if (results.empty()) {
        return NULL;
    }
    Result r = results.front();
    results.pop();
    return new Result(r);
}

Result GroupMatcher::mergeResults(Result& a, Result& b)
{
    unordered_map<string, forward_list<MatchableInterface *>> outputs{a.getOutputs()};
    auto outB = b.getOutputs();
    outputs.insert(outB.begin(), outB.end());
    size_t end = max(a.getLastMatchedIndex(), b.getLastMatchedIndex());
    return Result(start, end, outputs);
}

void GroupMatcher::recursiveMatch(
    size_t matcherIndex,
    const vector<MatchableInterface *> &matchables,
    size_t matchableIndex,
    forward_list<Result> &previousResults,
    Result& accResult
) {
    if (matcherIndex >= matchers.size() or
        matchableIndex > matchables.size() // > strict due to EndMatcher
    ) {
        return;
    }
    Result* r = matchers[matcherIndex]->match(
        matchables,
        matchableIndex,
        previousResults
    );
    while (r != NULL) {
        Result curRes(*r);
        delete r;
        previousResults.push_front(curRes);
        Result finalRes = mergeResults(accResult, curRes);
        if (matcherIndex == matchers.size() - 1) {
            results.push(finalRes);
        } else {
            recursiveMatch(
                matcherIndex + 1,
                matchables,
                curRes.getLastMatchedIndex() + 1,
                previousResults,
                finalRes
            );
        }
        previousResults.pop_front();
        r = matchers[matcherIndex]->next();
    }
}
