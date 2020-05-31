#include "RangeMatcher.hpp"

RangeMatcher::RangeMatcher(MatcherInterface *m, uint min, uint max)
{
    matcher = m;
    this->min = min;
    this->max = max;
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
    results = stack<Result*>();
    if (min == 0) {
        results.push(new Result(start - 1, start - 1));
    }
    uint nMatched = 0;
    size_t i = start;
    while (i < matchables.size()) {
        Result *r = matcher->match(matchables, i, previousResults);
        if (r == NULL) {
            break;
        }
        nMatched++;
        i = std::max(r->getLastMatchedIndex() + 1, int(i + 1));
        if (nMatched >= min and nMatched <= max) {
            results.push(new Result(
                start,
                r->getLastMatchedIndex(),
                r->getOutputs()
            ));
            // TODO: consider m->next() results somehow
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
