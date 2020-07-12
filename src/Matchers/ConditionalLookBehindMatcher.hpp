#pragma once
#include <string>
#include <forward_list>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"
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
