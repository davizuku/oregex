#pragma once
#include "PositiveLookAheadMatcher.hpp"
#include "MatcherInterface.hpp"

class NegativeLookAheadMatcher: public PositiveLookAheadMatcher
{
    public:
        NegativeLookAheadMatcher(MatcherInterface *matcher) : PositiveLookAheadMatcher(matcher){};

        Result* match(
            const vector<MatchableInterface *> &matchables,
            size_t start,
            const forward_list<Result> &previousResults
        );

        Result* match(
            const vector<MatchableInterface *> &matchables,
            size_t start
        );
};
