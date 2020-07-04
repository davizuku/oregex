#pragma once
#include <string>
#include <forward_list>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"
#include "MatcherInterface.hpp"

class ConditionalLookAheadMatcher: public MatcherInterface
{
    public:
        ConditionalLookAheadMatcher(
            MatcherInterface *condMatcher,
            MatcherInterface *trueMatcher,
            MatcherInterface *falseMatcher
        );
        ~ConditionalLookAheadMatcher();

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
        bool previousMatch;
        MatcherInterface* condMatcher;
        MatcherInterface* trueMatcher;
        MatcherInterface* falseMatcher;
        MatcherInterface* useMatcher;
};
