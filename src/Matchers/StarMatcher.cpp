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
        Result* r = matcher->match(matchables, i);
        if (r == NULL) {
            break;
        }
        while (r != NULL) {
            results.push_front(*r);
            r = matcher->next();
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
