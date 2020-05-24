#include "RangeMatcher.hpp"

RangeMatcher::RangeMatcher(MatcherInterface *m, uint min, uint max)
{
    matcher = m;
    this->min = min;
    this->max = max;
}

RangeMatcher::RangeMatcher(MatcherInterface *m)
{
    matcher = m;
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
    results = stack<Result*>();
    if (min == 0) {
        results.push(new Result(start - 1, start - 1));
    }
    uint nMatched = 0;
    for (size_t i = start; i < matchables.size(); ++i) {
        Result *r = matcher->match(matchables, i, previousResults);
        if (r == NULL) {
            break;
        }
        nMatched++;
        if (nMatched >= min and nMatched <= max) {
            while (r != NULL) {
                results.push(new Result(
                    start,
                    r->getLastMatchedIndex(),
                    r->getOutputs()
                ));
                r = matcher->next();
            }
        } else if (nMatched > max) {
            break;
        }
    }
    return next();
}

Result* RangeMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* RangeMatcher::next()
{
    if (results.empty()) {
        return NULL;
    }
    Result* r = results.top();
    results.pop();
    return r;
}
