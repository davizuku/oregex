#pragma once
#include "RangeMatcher.hpp"
#include "MatcherInterface.hpp"

class PlusMatcher : public RangeMatcher
{
public:
    PlusMatcher(MatcherInterface *m);
    ~PlusMatcher();
};
