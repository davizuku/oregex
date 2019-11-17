#pragma once
#include <forward_list>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"

using namespace std;

class MatcherInterface
{
    public:
        virtual forward_list<Result> match(forward_list<MatchableInterface*> matchables) = 0;
};
