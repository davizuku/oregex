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
    int n = matchables.size();
    for (int i = start; i < n; ++i) {
        MatchableInterface *m = matchables[i];
        if (m->getValue() == value) {
            results.push_front(Result(i));
            break;
        }
    }
    return results;
}

forward_list<Result> StringMatcher::match(
    const vector<MatchableInterface *> &matchables,
    int start
) {
    return match(matchables, start, forward_list<Result>{});
}
