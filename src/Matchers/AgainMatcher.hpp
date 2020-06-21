#pragma once
#include <string>
#include <forward_list>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"
#include "MatcherInterface.hpp"

class AgainMatcher: public MatcherInterface
{
    public:
        AgainMatcher(string outputName);
        ~AgainMatcher();

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
        size_t start;
        MatcherInterface *matcher;
        vector<MatchableInterface *> matchables;
        forward_list<Result> previousResults;
        forward_list<Result>::const_iterator curResult;
};
