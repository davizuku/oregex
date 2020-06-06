#include "ExactlyMatcher.hpp"

ExactlyMatcher::ExactlyMatcher(MatcherInterface *m, uint n) : RangeMatcher(m, n, n)
{
}

ExactlyMatcher::~ExactlyMatcher()
{
}
