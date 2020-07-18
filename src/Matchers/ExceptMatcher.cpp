#include "ExceptMatcher.hpp"

ExceptMatcher::ExceptMatcher(const vector<MatcherInterface *> &matchers)
{
    this->matchers = matchers;
}

ExceptMatcher::~ExceptMatcher()
{
}

Result* ExceptMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    if (start >= matchables.size()) {
        return NULL;
    }
    for (MatcherInterface* m : matchers) {
        Result *r = m->match(matchables, start, previousResults);
        if (r != NULL) {
            delete r;
            return NULL;
        }
    }
    return new Result(start, start);
}

Result* ExceptMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* ExceptMatcher::next()
{
    return NULL;
}
