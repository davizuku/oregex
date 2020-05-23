#include "StringMatcher.hpp"

StringMatcher::StringMatcher(string s)
{
    valueSize = s.length();
    value = new char[valueSize+1];
    strcpy(value, s.c_str());
}

StringMatcher::~StringMatcher()
{
}

Result* StringMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    if (start >= matchables.size()) {
        return NULL;
    }
    string input = matchables[start]->getValue();
    if (input.length() == valueSize and
        input[0] == value[0] and
        memcmp(input.c_str(), value, valueSize) == 0
    ) {
        return new Result(start, start);
    }
    return NULL;
}

Result* StringMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* StringMatcher::next()
{
    return NULL;
}
