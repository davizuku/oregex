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
    return NULL;
}

Result* OrMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* OrMatcher::next()
{
    return NULL;
}
