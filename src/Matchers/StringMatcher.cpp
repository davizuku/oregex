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
    string input = matchables[start]->getValue();
    if (input[0] == value[0] and input == value) {
        return new Result(start);
    }
    return NULL;
}

Result* StringMatcher::match(
    const vector<MatchableInterface *> &matchables,
    int start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* StringMatcher::next()
{
    return NULL;
}
