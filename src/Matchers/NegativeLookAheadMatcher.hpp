#pragma once
#include "PositiveLookAheadMatcher.hpp"
#include "MatcherInterface.hpp"

class NegativeLookAheadMatcher: public PositiveLookAheadMatcher
{
    public:
        NegativeLookAheadMatcher(MatcherInterface *matcher);
        ~NegativeLookAheadMatcher();
};
