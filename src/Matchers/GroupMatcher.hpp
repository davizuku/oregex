#pragma once
#include <forward_list>
#include <list>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"
#include "MatcherInterface.hpp"

class GroupMatcher: public MatcherInterface
{
    public:
        GroupMatcher(const vector<MatcherInterface *> &matchers);
        ~GroupMatcher();

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
        vector<MatcherInterface *> matchers;
        list<Result*> results;
        list<Result*>::iterator resultIt;

        void recursiveMatch(
            size_t matcherIndex,
            const vector<MatchableInterface *> &matchables,
            size_t matchableIndex,
            forward_list<Result> &previousResults,
            Result* accResult
        );
};
