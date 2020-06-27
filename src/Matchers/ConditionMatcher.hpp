#pragma once
#include <string>
#include <forward_list>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"
#include "MatcherInterface.hpp"

class ConditionMatcher: public MatcherInterface
{
    public:
        ConditionMatcher(
            string outputName,
            MatcherInterface *trueMatcher,
            MatcherInterface *falseMatcher
        );
        ~ConditionMatcher();

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
        string outputName;
        bool previousMatch;
        MatcherInterface* trueMatcher;
        MatcherInterface* falseMatcher;

        bool hasOutputName(const forward_list<Result> &previousResults);
};
