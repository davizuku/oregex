#include "StarMatcher.hpp"

StarMatcher::StarMatcher(MatcherInterface *m)
{
    matcher = m;
}

StarMatcher::~StarMatcher()
{
}

forward_list<Result> StarMatcher::match(
    const vector<MatchableInterface *> &matchables,
    int start,
    const forward_list<Result> &previousResults
) {
    forward_list<Result> results{Result(start-1)};
    int n = matchables.size();
    for (int i = start; i < n; ++i) {
        auto subResults = matcher->match(matchables, i);
        for (Result r: subResults) {
            results.push_front(r);
        }
        if (subResults.empty()) {
            break;
        }
    }
    return results;
}

forward_list<Result> StarMatcher::match(
    const vector<MatchableInterface *> &matchables,
    int start
) {
    return match(matchables, start, forward_list<Result>{});
}
