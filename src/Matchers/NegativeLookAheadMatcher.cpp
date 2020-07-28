#include "NegativeLookAheadMatcher.hpp"
#include "ExceptMatcher.hpp"

Result *NegativeLookAheadMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    ExceptMatcher em(vector<MatcherInterface *>{this->matcher});
    this->matcher = &em;
    return PositiveLookAheadMatcher::match(matchables, start, previousResults);
}

Result *NegativeLookAheadMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}
