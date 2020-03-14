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

        Result* match(
            const vector<MatchableInterface *> &matchables,
            int start,
            const forward_list<Result> &previousResults
        );

        Result* match(
            const vector<MatchableInterface *> &matchables,
            int start
        );

        Result* next();

    protected:
        vector<MatcherInterface *> matchers;
        forward_list<Result> results;
        forward_list<Result>::iterator lastResultIterator;

        void recursiveMatch(
            int matcherIndex,
            const vector<MatchableInterface *> &matchables,
            int matchableIndex,
            forward_list<Result> &previousResults,
            forward_list<Result> &recursiveResults
        );
};
