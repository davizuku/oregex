#include "PositiveLookAheadMatcher.hpp"

PositiveLookAheadMatcher::PositiveLookAheadMatcher(MatcherInterface *matcher)
{
    this->matcher = matcher;
}

PositiveLookAheadMatcher::~PositiveLookAheadMatcher()
{
}

Result *PositiveLookAheadMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults)
{
    if (start < matchables.size() and
        this->matcher->match(matchables, start, previousResults) != NULL
    ) {
        return new Result(start - 1, start - 1);
    }
    return NULL;
}

Result *PositiveLookAheadMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start)
{
    return match(matchables, start, forward_list<Result>{});
}

Result *PositiveLookAheadMatcher::next()
{
    return NULL;
}
