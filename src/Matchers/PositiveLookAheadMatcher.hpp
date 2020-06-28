#pragma once
#include "MatcherInterface.hpp"

class PositiveLookAheadMatcher: public MatcherInterface
{
    public:
        PositiveLookAheadMatcher(MatcherInterface *matcher);
        ~PositiveLookAheadMatcher();

        Result* match(
            const vector<MatchableInterface *> &matchables,
            size_t start,
            const forward_list<Result> &previousResults
        );

        Result* match(
            const vector<MatchableInterface *> &matchables,
            size_t start
        );

        Result* next();

    protected:
        MatcherInterface* matcher;
};
