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
        MatcherInterface *matcher;
};