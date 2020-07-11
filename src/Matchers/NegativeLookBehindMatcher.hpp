#pragma once
#include "MatcherInterface.hpp"

class NegativeLookBehindMatcher: public MatcherInterface
{
    public:
        NegativeLookBehindMatcher(MatcherInterface *matcher);
        ~NegativeLookBehindMatcher();

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
