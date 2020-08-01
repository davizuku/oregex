#pragma once
#include <string>
#include <forward_list>
#include <queue>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"
#include "MatcherInterface.hpp"

class NamedGroupMatcher: public MatcherInterface
{
    public:
        NamedGroupMatcher(string name, MatcherInterface *m);
        ~NamedGroupMatcher();

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
        queue<Result*> results;
        string name;
};
