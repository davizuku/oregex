#pragma once
#include "MatcherInterface.hpp"

class PositiveLookBehindMatcher: public MatcherInterface
{
    public:
        PositiveLookBehindMatcher(MatcherInterface *matcher);
        ~PositiveLookBehindMatcher();

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
