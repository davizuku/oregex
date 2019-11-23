#pragma once
#include <forward_list>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"

using namespace std;

class MatcherInterface
{
public:
    /**
     * A vector is used for matchables due to the fact that some matchers may
     * need to iterate backwards to resolve the match.
     * For example: lookbehind (positive, negative, conditional)
     */
    virtual forward_list<Result> match(
        vector<MatchableInterface *> matchables,
        int start
    ) = 0;
};
