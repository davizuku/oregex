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
        if (m->match(matchables, start, previousResults) != NULL) {
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
