#pragma once
#include <string>
#include <forward_list>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"
#include "MatcherInterface.hpp"

using namespace std;

class StringMatcher: public MatcherInterface
{
    public:
        StringMatcher(string s);
        ~StringMatcher();

        forward_list<Result> match(
            vector<MatchableInterface *> matchables,
            int start,
            forward_list<Result> previousResults
        );

        forward_list<Result> match(
            vector<MatchableInterface *> matchables,
            int start
        );

    protected:
        string value;
};
