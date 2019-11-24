#include "StringMatcher.hpp"

StringMatcher::StringMatcher(string s)
{
    value = s;
}

StringMatcher::~StringMatcher()
{
}

forward_list<Result> StringMatcher::match(
    const vector<MatchableInterface *> &matchables,
    int start,
    const forward_list<Result> &previousResults
) {
    forward_list<Result> results;
    if (matchables[start]->getValue() == value) {
        results.push_front(Result(start));
    }
    return results;
}

forward_list<Result> StringMatcher::match(
    const vector<MatchableInterface *> &matchables,
    int start
) {
    return match(matchables, start, forward_list<Result>{});
}
