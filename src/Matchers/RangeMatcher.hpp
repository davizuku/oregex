#pragma once
#include <string>
#include <forward_list>
#include <stack>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"
#include "MatcherInterface.hpp"

class RangeMatcher: public MatcherInterface
{
    public:
        RangeMatcher(MatcherInterface *m, uint min, uint max);
        RangeMatcher(MatcherInterface *m, uint min);
        RangeMatcher(MatcherInterface *m);
        ~RangeMatcher();

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
        uint min, max;
        MatcherInterface *matcher;
        stack<Result*> results;
};