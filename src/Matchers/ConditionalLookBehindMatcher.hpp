#pragma once
#include "ConditionalLookAheadMatcher.hpp"

class ConditionalLookBehindMatcher: public ConditionalLookAheadMatcher
{
    public:
        ConditionalLookBehindMatcher(
            MatcherInterface *condMatcher,
            MatcherInterface *trueMatcher,
            MatcherInterface *falseMatcher
        );
        ~ConditionalLookBehindMatcher();
};
