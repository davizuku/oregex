#pragma once
#include <string>
#include <forward_list>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"
#include "MatcherInterface.hpp"

class GroupMatcher: public MatcherInterface
{
    public:
        GroupMatcher(const vector<MatcherInterface *> &matchers);
        ~GroupMatcher();

        forward_list<Result> match(
            const vector<MatchableInterface *> &matchables,
            int start,
            const forward_list<Result> &previousResults
        );

        forward_list<Result> match(
            const vector<MatchableInterface *> &matchables,
            int start
        );

    protected:
        vector<MatcherInterface *> matchers;
        forward_list<Result> results;

        void recursiveMatch(
            int matcherIndex,
            const vector<MatchableInterface *> &matchables,
            int matchableIndex,
            const forward_list<Result> &previousResults
        );
};
