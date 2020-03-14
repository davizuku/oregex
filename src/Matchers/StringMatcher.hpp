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
        forward_list<Result> results;
        forward_list<Result>::iterator lastResultIterator;
        string value;
};
