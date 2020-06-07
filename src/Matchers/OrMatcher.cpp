#include "OrMatcher.hpp"

OrMatcher::OrMatcher(const vector<MatcherInterface *> &m)
{
    matchers = m;
}

OrMatcher::~OrMatcher()
{
}

Result* OrMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    if (start >= matchables.size()) {
        return NULL;
    }
    this->start = start;
    this->matchables = matchables;
    this->previousResults = previousResults;
    matcherIndex = 0;
    matchCalled = false;
    return next();
}

Result* OrMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* OrMatcher::next()
{
    if (matchCalled) {
        Result* r = matchers[matcherIndex]->next();
        if (r != NULL) {
            return r;
        }
        matchCalled = false;
        matcherIndex++;
    }
    for (int i = matcherIndex; i < matchers.size(); i++) {
        Result *r = matchers[i]->match(matchables, start, previousResults);
        matchCalled = true;
        if (r != NULL) {
            matcherIndex = i;
            return r;
        }
    }
    return NULL;
}
