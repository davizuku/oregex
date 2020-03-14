#include "StarMatcher.hpp"

StarMatcher::StarMatcher(MatcherInterface *m)
{
    matcher = m;
}

StarMatcher::~StarMatcher()
{
}

Result* StarMatcher::match(
    const vector<MatchableInterface *> &matchables,
    int start,
    const forward_list<Result> &previousResults
) {
    results = forward_list<Result>{Result(start - 1)};
    int n = matchables.size();
    for (int i = start; i < n; ++i) {
        forward_list<Result> subResults{};
        Result* r = matcher->match(matchables, i);
        while (r != NULL) {
            subResults.push_front(*r);
            r = matcher->next();
        }
        subResults.reverse();
        for (Result r: subResults) {
            results.push_front(r);
        }
        if (subResults.empty()) {
            break;
        }
    }
    lastResultIterator = results.before_begin();
    return next();
}

Result* StarMatcher::match(
    const vector<MatchableInterface *> &matchables,
    int start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* StarMatcher::next()
{
    ++lastResultIterator;
    if (lastResultIterator == results.end()) {
        return NULL;
    }
    return &(*lastResultIterator);
}
