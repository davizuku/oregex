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

        Result match(forward_list<MatchableInterface *> matchables);

    protected:
        string value;
};
