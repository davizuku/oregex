#pragma once
#include <forward_list>
#include <queue>
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
        size_t start;
        vector<MatcherInterface *> matchers;
        queue<Result> results;
        Result mergeResults(Result& a, Result& b);

        void recursiveMatch(
            size_t matcherIndex,
            const vector<MatchableInterface *> &matchables,
            size_t matchableIndex,
            forward_list<Result> &previousResults,
            Result& accResult
        );
};
