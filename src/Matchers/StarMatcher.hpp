#pragma once
#include <string>
#include <forward_list>
#include <stack>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"
#include "MatcherInterface.hpp"

class StarMatcher: public MatcherInterface
{
    public:
        StarMatcher(MatcherInterface *m);
        ~StarMatcher();

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
        MatcherInterface *matcher;
        stack<Result*> results;
};
