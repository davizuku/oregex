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
    Result *r = condMatcher->match(matchables, start, previousResults);
    useMatcher = (r != NULL) ? trueMatcher : falseMatcher;
    delete r;
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
