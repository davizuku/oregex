#include "AnyMatcher.hpp"

AnyMatcher::AnyMatcher()
{
}

AnyMatcher::~AnyMatcher()
{
}

Result* AnyMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    if (start >= matchables.size()) {
        return NULL;
    }
    return new Result(start, start);
}

Result* AnyMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* AnyMatcher::next()
{
    return NULL;
}
