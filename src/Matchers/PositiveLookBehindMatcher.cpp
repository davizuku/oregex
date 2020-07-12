#include "PositiveLookBehindMatcher.hpp"

PositiveLookBehindMatcher::PositiveLookBehindMatcher(MatcherInterface *matcher)
{
    this->matcher = matcher;
}

PositiveLookBehindMatcher::~PositiveLookBehindMatcher()
{
}

Result *PositiveLookBehindMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults)
{
    if (start > 0 and start < matchables.size()) {
        for (int i = start - 1; i >= 0; --i) {
            Result *r = this->matcher->match(matchables, i, previousResults);
            while (r != NULL) {
                if (r->getLastMatchedIndex() == start - 1) {
                    return new Result(start -1, start - 1);
                }
                r = this->matcher->next();
            }
        }
    }
    return NULL;
}

Result *PositiveLookBehindMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start)
{
    return match(matchables, start, forward_list<Result>{});
}

Result *PositiveLookBehindMatcher::next()
{
    return NULL;
}
