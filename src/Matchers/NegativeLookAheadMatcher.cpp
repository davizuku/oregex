#include "NegativeLookAheadMatcher.hpp"
#include "ExceptMatcher.hpp"

Result *NegativeLookAheadMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    MatcherInterface* subMatcher = matcher;
    matcher = new ExceptMatcher(vector<MatcherInterface *>{subMatcher});
    Result* r = PositiveLookAheadMatcher::match(matchables, start, previousResults);
    delete (ExceptMatcher*)matcher;
    matcher = subMatcher;
    return r;
}

Result *NegativeLookAheadMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}
