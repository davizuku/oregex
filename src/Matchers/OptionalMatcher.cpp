#include "OptionalMatcher.hpp"

OptionalMatcher::OptionalMatcher(MatcherInterface *m) : RangeMatcher(m, 0, 1)
{
}

OptionalMatcher::~OptionalMatcher()
{
}
