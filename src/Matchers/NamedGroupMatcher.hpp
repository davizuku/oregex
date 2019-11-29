#pragma once
#include <string>
#include <forward_list>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"
#include "MatcherInterface.hpp"

class NamedGroupMatcher: public MatcherInterface
{
    public:
        NamedGroupMatcher(string name, MatcherInterface *m);
        ~NamedGroupMatcher();

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
        string name;
};
