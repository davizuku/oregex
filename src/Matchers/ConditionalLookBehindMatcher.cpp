#include "ConditionalLookBehindMatcher.hpp"
#include "PositiveLookBehindMatcher.hpp"

Result *ConditionalLookBehindMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults)
{
    MatcherInterface* subMatcher = condMatcher;
    condMatcher = new PositiveLookBehindMatcher(subMatcher);
    Result* r = ConditionalLookAheadMatcher::match(matchables, start, previousResults);
    delete (PositiveLookBehindMatcher*)condMatcher;
    condMatcher = subMatcher;
    return r;
}

Result *ConditionalLookBehindMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}
