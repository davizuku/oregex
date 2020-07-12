#include "NegativeLookBehindMatcher.hpp"

NegativeLookBehindMatcher::NegativeLookBehindMatcher(MatcherInterface *matcher)
{
    this->matcher = matcher;
}

NegativeLookBehindMatcher::~NegativeLookBehindMatcher()
{
}

Result *NegativeLookBehindMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults)
{
    if (start < matchables.size()) {
        for (int i = start - 1; i >= 0; --i) {
            Result *r = this->matcher->match(matchables, i, previousResults);
            while (r != NULL) {
                if (r->getLastMatchedIndex() == start - 1) {
                    return NULL;
                }
                r = this->matcher->next();
            }
        }
        return new Result(start -1, start - 1);
    }
    return NULL;
}

Result *NegativeLookBehindMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start)
{
    return match(matchables, start, forward_list<Result>{});
}

Result *NegativeLookBehindMatcher::next()
{
    return NULL;
}
