#pragma once
#include <string>
#include <forward_list>
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
            int start,
            const forward_list<Result> &previousResults
        );

        Result* match(
            const vector<MatchableInterface *> &matchables,
            int start
        );

        Result* next();

    protected:
        MatcherInterface *matcher;
        forward_list<Result> results;
        forward_list<Result>::iterator lastResultIterator;
};
