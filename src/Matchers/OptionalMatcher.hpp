#pragma once
#include "RangeMatcher.hpp"
#include "MatcherInterface.hpp"

class OptionalMatcher: public RangeMatcher
{
    public:
        OptionalMatcher(MatcherInterface *m);
        ~OptionalMatcher();
};
