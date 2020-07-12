#include "UngreedyMatcher.hpp"

UngreedyMatcher::UngreedyMatcher(MatcherInterface* m)
{
    matcher = m;
}

UngreedyMatcher::~UngreedyMatcher()
{
}

Result* UngreedyMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    results = stack<Result*>();
    Result* r = matcher->match(matchables, start, previousResults);
    do {
        results.push(r);
        r = matcher->next();
    } while (r != NULL);
    return next();
}

Result* UngreedyMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* UngreedyMatcher::next()
{
    if (results.empty()) {
        return NULL;
    }
    Result* r = results.top();
    results.pop();
    return r;
}
