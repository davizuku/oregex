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
     *
     * Returns the greediest Result.
     */
    virtual Result* match(
        const vector<MatchableInterface *> &matchables,
        int start,
        const forward_list<Result> &previousResults
    ) = 0;

    virtual Result* match(
        const vector<MatchableInterface *> &matchables,
        int start
    ) = 0;

    /**
     * To be used after a call to match(...).
     * Every call to next() returns the next Result ordered from the most greedy
     * to the most ungreedy. Each Result is considered starting in matchables[start].
     */
    virtual Result* next() = 0;
};
