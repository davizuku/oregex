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
     *
     * Previous results are needed because some matchers may need to reference
     * previous matched results.
     * For example: recursive conditional statement, backreference /('|")\w+\1/
     */
    virtual forward_list<Result> match(
        const vector<MatchableInterface *> &matchables,
        int start,
        const forward_list<Result> &previousResults
    ) = 0;

    virtual forward_list<Result> match(
        const vector<MatchableInterface *> &matchables,
        int start
    ) = 0;
};
