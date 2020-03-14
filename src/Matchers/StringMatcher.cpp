#include "StringMatcher.hpp"

StringMatcher::StringMatcher(string s)
{
    value = s;
}

StringMatcher::~StringMatcher()
{
}

Result* StringMatcher::match(
    const vector<MatchableInterface *> &matchables,
    int start,
    const forward_list<Result> &previousResults
) {
    results = forward_list<Result>{};
    if (matchables[start]->getValue() == value) {
        results.push_front(Result(start));
    }
    lastResultIterator = results.before_begin();
    return next();
}

Result* StringMatcher::match(
    const vector<MatchableInterface *> &matchables,
    int start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* StringMatcher::next()
{
    ++lastResultIterator;
    if (lastResultIterator == results.end()) {
        return NULL;
    }
    return &(*lastResultIterator);
}
