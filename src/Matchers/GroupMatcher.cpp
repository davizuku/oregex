#include "GroupMatcher.hpp"

GroupMatcher::GroupMatcher(const vector<MatcherInterface *> &m)
{
    matchers = m;
}

GroupMatcher::~GroupMatcher()
{
}

forward_list<Result> GroupMatcher::match(
    const vector<MatchableInterface *> &matchables,
    int start,
    const forward_list<Result> &previousResults
) {
    auto copyPrevResults = previousResults;
    auto recursiveResults = forward_list<Result>{};
    results = forward_list<Result>{};
    recursiveMatch(
        0,
        matchables,
        start,
        copyPrevResults,
        recursiveResults
    );
    results.reverse();
    return results;
}

forward_list<Result> GroupMatcher::match(
    const vector<MatchableInterface *> &matchables,
    int start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result mergeOutputs(forward_list<Result> &results)
{
    int index = -1;
    map<string, forward_list<MatchableInterface *>> outputs{};
    for (Result &r: results) {
        index = max(index, r.getLastMatchedIndex());
        auto rOuts = r.getOutputs();
        outputs.insert(rOuts.begin(), rOuts.end());
    }
    return Result(index, outputs);
}

void GroupMatcher::recursiveMatch(
    int matcherIndex,
    const vector<MatchableInterface *> &matchables,
    int matchableIndex,
    forward_list<Result> &previousResults,
    forward_list<Result> &recursiveResults
) {
    if (matcherIndex >= matchers.size() or matchableIndex >= matchables.size()) {
        return;
    }
    forward_list<Result> subResults = matchers[matcherIndex]->match(
        matchables,
        matchableIndex,
        previousResults
    );
    for (Result &r : subResults) {
        recursiveResults.push_front(r);
        previousResults.push_front(r);
        if (matcherIndex == matchers.size() - 1) {
            Result finalRes = mergeOutputs(recursiveResults);
            results.push_front(finalRes);
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
