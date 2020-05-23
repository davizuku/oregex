#include "EndMatcher.hpp"

EndMatcher::EndMatcher()
{
}

EndMatcher::~EndMatcher()
{
}

Result* EndMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    if (start == matchables.size()) {
        return new Result(start, start);
    }
    return NULL;
}

Result* EndMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* EndMatcher::next()
{
    return NULL;
}
