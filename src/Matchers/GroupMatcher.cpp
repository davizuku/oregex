#include "GroupMatcher.hpp"

GroupMatcher::GroupMatcher(vector<MatcherInterface *> &m)
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
    results = forward_list<Result>{};
    recursiveMatch(0, matchables, start, previousResults);
    results.reverse();
    return results;
}

forward_list<Result> GroupMatcher::match(
    const vector<MatchableInterface *> &matchables,
    int start
) {
    return match(matchables, start, forward_list<Result>{});
}

void GroupMatcher::recursiveMatch(
    int matcherIndex,
    const vector<MatchableInterface *> &matchables,
    int matchableIndex,
    const forward_list<Result> &previousResults)
{
    if (matcherIndex >= matchers.size() or matchableIndex >= matchables.size()) {
        return;
    }
    forward_list<Result> subResults = matchers[matcherIndex]->match(
        matchables,
        matchableIndex,
        previousResults
    );
    for (Result &r : subResults) {
        if (matcherIndex == matchers.size() - 1) {
            results.push_front(r);
        } else {
            recursiveMatch(
                matcherIndex + 1,
                matchables,
                r.getLastMatchedIndex() + 1,
                results
            );
        }
    }
}
