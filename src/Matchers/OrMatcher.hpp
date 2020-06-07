#pragma once
#include <vector>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"
#include "MatcherInterface.hpp"

class OrMatcher: public MatcherInterface
{
    public:
        OrMatcher(const vector<MatcherInterface *> &m);
        ~OrMatcher();

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
        vector<MatcherInterface*> matchers;
        size_t matcherIndex;
        bool matchCalled;

        size_t start;
        vector<MatchableInterface *> matchables;
        forward_list<Result> previousResults;
};
