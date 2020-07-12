#include "ConditionalLookBehindMatcher.hpp"
#include "PositiveLookBehindMatcher.hpp"

ConditionalLookBehindMatcher::ConditionalLookBehindMatcher(
    MatcherInterface* condMatcher,
    MatcherInterface* trueMatcher,
    MatcherInterface* falseMatcher
) : ConditionalLookAheadMatcher(
    new PositiveLookBehindMatcher(condMatcher),
    trueMatcher,
    falseMatcher
) {}

ConditionalLookBehindMatcher::~ConditionalLookBehindMatcher()
{
}
