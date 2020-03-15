#include "GroupMatcher.hpp"

GroupMatcher::GroupMatcher(const vector<MatcherInterface *> &m)
{
    matchers = m;
}

GroupMatcher::~GroupMatcher()
{
}

Result* GroupMatcher::match(
    const vector<MatchableInterface *> &matchables,
    int start,
    const forward_list<Result> &previousResults
) {
    auto copyPrevResults = previousResults;
    auto recursiveResults = forward_list<Result>{};
    results = queue<Result*>();
    recursiveMatch(
        0,
        matchables,
        start,
        copyPrevResults,
        recursiveResults
    );
    return next();
}

Result* GroupMatcher::match(
    const vector<MatchableInterface *> &matchables,
    int start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* GroupMatcher::next()
{
    if (results.empty()) {
        return NULL;
    }
    Result* r = results.front();
    results.pop();
    return r;
}

Result* mergeOutputs(forward_list<Result> &results)
{
    int index = -1;
    map<string, forward_list<MatchableInterface *>> outputs{};
    for (Result &r: results) {
        index = max(index, r.getLastMatchedIndex());
        auto rOuts = r.getOutputs();
        outputs.insert(rOuts.begin(), rOuts.end());
    }
    return new Result(index, outputs);
}

void GroupMatcher::recursiveMatch(
    int matcherIndex,
    const vector<MatchableInterface *> &matchables,
    int matchableIndex,
    forward_list<Result> &previousResults,
    forward_list<Result> &recursiveResults
) {
    if (matcherIndex >= (int)matchers.size() or
        matchableIndex >= (int)matchables.size()
    ) {
        return;
    }
    forward_list<Result> subResults{};
    Result* r = matchers[matcherIndex]->match(
        matchables,
        matchableIndex,
        previousResults
    );
    while (r != NULL) {
        subResults.push_front(*r);
        r = matchers[matcherIndex]->next();
    }
    subResults.reverse();
    for (Result &r : subResults) {
        recursiveResults.push_front(r);
        previousResults.push_front(r);
        if (matcherIndex == (int)matchers.size() - 1) {
            Result* finalRes = mergeOutputs(recursiveResults);
            results.push(finalRes);
        } else {
            recursiveMatch(
                matcherIndex + 1,
                matchables,
                r.getLastMatchedIndex() + 1,
                previousResults,
                recursiveResults
            );
        }
        recursiveResults.pop_front();
        previousResults.pop_front();
    }
}
