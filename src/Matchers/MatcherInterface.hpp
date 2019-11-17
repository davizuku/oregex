#pragma once
#include <vector>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"

using namespace std;

class MatcherInterface
{
    public:
        virtual Result match(vector<MatchableInterface *> matchables) = 0;
};
