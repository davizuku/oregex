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
    results = stack<Result*>();
    results.push(new Result(start - 1));
    int n = matchables.size();
    for (int i = start; i < n; ++i) {
        Result* r = matcher->match(matchables, i, previousResults);
        if (r == NULL) {
            break;
        }
        while (r != NULL) {
            results.push(r);
            r = matcher->next();
        }
    }
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
    if (results.empty()) {
        return NULL;
    }
    Result* r = results.top();
    results.pop();
    return r;
}
