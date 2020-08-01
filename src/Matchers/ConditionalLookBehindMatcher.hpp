#pragma once
#include "ConditionalLookAheadMatcher.hpp"

class ConditionalLookBehindMatcher: public ConditionalLookAheadMatcher
{
    public:
        ConditionalLookBehindMatcher(
            MatcherInterface *condMatcher,
            MatcherInterface *trueMatcher,
            MatcherInterface *falseMatcher
        ) : ConditionalLookAheadMatcher(condMatcher, trueMatcher, falseMatcher){};

        Result *match(
            const vector<MatchableInterface *> &matchables,
            size_t start,
            const forward_list<Result> &previousResults
        );

        Result *match(
            const vector<MatchableInterface *> &matchables,
            size_t start
        );
};
