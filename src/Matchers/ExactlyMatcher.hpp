#pragma once
#include "RangeMatcher.hpp"
#include "MatcherInterface.hpp"

class ExactlyMatcher: public RangeMatcher
{
    public:
        ExactlyMatcher(MatcherInterface *m, uint n);
        ~ExactlyMatcher();
};
