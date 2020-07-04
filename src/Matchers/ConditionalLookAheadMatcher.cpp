#include "ConditionalLookAheadMatcher.hpp"

ConditionalLookAheadMatcher::ConditionalLookAheadMatcher(
    MatcherInterface* condMatcher,
    MatcherInterface* trueMatcher,
    MatcherInterface* falseMatcher
) {
    this->condMatcher = condMatcher;
    this->trueMatcher = trueMatcher;
    this->falseMatcher = falseMatcher;
}

ConditionalLookAheadMatcher::~ConditionalLookAheadMatcher()
{
}

Result* ConditionalLookAheadMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    if (start >= matchables.size()) {
        return NULL;
    }
    useMatcher = condMatcher->match(matchables, start, previousResults) != NULL ?
        trueMatcher :
        falseMatcher;
    return useMatcher->match(matchables, start, previousResults);
}

Result* ConditionalLookAheadMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* ConditionalLookAheadMatcher::next()
{
    return useMatcher->next();
}
