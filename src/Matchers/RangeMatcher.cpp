#include "RangeMatcher.hpp"

RangeMatcher::RangeMatcher(MatcherInterface *m, uint min, uint max)
{
    matcher = m;
    this->min = min;
    this->max = min == 0 ? max + 1 : max;
}

RangeMatcher::RangeMatcher(MatcherInterface *m, uint min)
{
    matcher = m;
    this->min = min;
    this->max = -1;
}

RangeMatcher::RangeMatcher(MatcherInterface *m)
{
    matcher = m;
    this->min = 0;
    this->max = -1;
}

RangeMatcher::~RangeMatcher()
{
}

Result* RangeMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    if (start >= matchables.size()) {
        return NULL;
    }
    this->start = start;
    this->matchables = matchables;
    this->previousResults = previousResults;
    matchingStack = stack<queue<Result *>>();
    visitedIndices = vector<bool>(matchables.size(), false);
    if (min == 0) {
        auto zeroLevel = queue<Result *>();
        zeroLevel.push(new Result(start - 1, start - 1));
        matchingStack.push(zeroLevel);
    }
    stackNewMatching(start);
    return next();
}

Result* RangeMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result *RangeMatcher::next()
{
    if (matchingStack.empty()) {
        return NULL;
    }
    if (matchingStack.top().empty()) {
        matchingStack.pop();
        return next();
    }
    Result* topFront = matchingStack.top().front();
    size_t stackSize = matchingStack.size();
    if (stackSize == max) {
        matchingStack.top().pop();
        return topFront;
    } else if (stackSize < min) {
        matchingStack.top().pop();
        stackNewMatching(topFront->getLastMatchedIndex() + 1);
        return next();
    } else if (stackSize < max) {
        stackNewMatching(topFront->getLastMatchedIndex() + 1);
        if (matchingStack.size() == stackSize) {
            // stackNewMatching did not find any new match
            matchingStack.top().pop();
            return topFront;
        }
        return next();
    }
    return NULL;
}

void RangeMatcher::stackNewMatching(size_t index)
{
    if (index >= visitedIndices.size() or visitedIndices[index]) {
        return; // This function has already been called with index value.
    }
    visitedIndices[index] = true;
    Result* r = matcher->match(matchables, index, previousResults);
    if (r != NULL) {
        auto newLevel = queue<Result*>();
        while (r != NULL) {
            newLevel.push(new Result(start, r->getLastMatchedIndex(), r->getOutputs()));
            r = matcher->next();
        }
        matchingStack.push(newLevel);
    }
}
