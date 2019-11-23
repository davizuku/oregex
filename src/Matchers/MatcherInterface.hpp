#pragma once
#include <forward_list>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"

using namespace std;

class MatcherInterface
{
public:
    virtual forward_list<Result> match(
        vector<MatchableInterface *> matchables,
        int start
    ) = 0;
};
