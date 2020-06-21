#include "AgainMatcher.hpp"

AgainMatcher::AgainMatcher(string outputName)
{
    this->outputName = outputName;
}

AgainMatcher::~AgainMatcher()
{
}

Result* AgainMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    if (start >= matchables.size()) {
        return NULL;
    }
    return new Result(start, start);
}

Result* AgainMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return NULL;
}

Result* AgainMatcher::next()
{
    return NULL;
}
