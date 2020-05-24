#pragma once
#include "RangeMatcher.hpp"
#include "MatcherInterface.hpp"

class StarMatcher: public RangeMatcher
{
    public:
        StarMatcher(MatcherInterface *m);
        ~StarMatcher();
};
