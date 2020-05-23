#include "RangeMatcher.hpp"

RangeMatcher::RangeMatcher(MatcherInterface *m)
{
    matcher = m;
}

RangeMatcher::~RangeMatcher()
{
}

Result* RangeMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    if (start >= matchables.size()) {
        return NULL;
    }
}

Result* RangeMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* RangeMatcher::next()
{
    if (results.empty()) {
        return NULL;
    }
    Result* r = results.top();
    results.pop();
    return r;
}
