#include "ConditionalLookBehindMatcher.hpp"
#include "PositiveLookBehindMatcher.hpp"

Result *ConditionalLookBehindMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults)
{
    PositiveLookBehindMatcher pbm(condMatcher);
    condMatcher = &pbm;
    return ConditionalLookAheadMatcher::match(matchables, start, previousResults);
}

Result *ConditionalLookBehindMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}
