#include "StartMatcher.hpp"

StartMatcher::StartMatcher()
{
}

StartMatcher::~StartMatcher()
{
}

Result* StartMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    if (start == 0) {
        return new Result(-1, -1);
    }
    return NULL;
}

Result* StartMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* StartMatcher::next()
{
    return NULL;
}
