#pragma once
#include <string>
#include <vector>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"
#include "MatcherInterface.hpp"

using namespace std;

class StringMatcher: public MatcherInterface
{
    public:
        StringMatcher(string s);
        ~StringMatcher();

        Result match(vector<MatchableInterface *> matchables);

    protected:
        string value;
};
