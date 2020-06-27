#include "ConditionMatcher.hpp"

ConditionMatcher::ConditionMatcher(
    string outputName,
    MatcherInterface* trueMatcher,
    MatcherInterface* falseMatcher
) {
    this->outputName = outputName;
    this->trueMatcher = trueMatcher;
    this->falseMatcher = falseMatcher;
    this->previousMatch = false;
}

ConditionMatcher::~ConditionMatcher()
{
}

Result* ConditionMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    if (start >= matchables.size()) {
        return NULL;
    }
    previousMatch = hasOutputName(previousResults);
    return previousMatch ?
        trueMatcher->match(matchables, start, previousResults) :
        falseMatcher->match(matchables, start, previousResults);
}

bool ConditionMatcher::hasOutputName(const forward_list<Result> &previousResults)
{
    for (auto it = previousResults.begin(); it != previousResults.end(); ++it) {
        auto outputs = it->getOutputs();
        for (auto out : outputs) {
            if (out.first == outputName) {
                return true;
            }
        }
    }
    return false;
}

Result* ConditionMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* ConditionMatcher::next()
{
    return previousMatch ? trueMatcher->next() : falseMatcher->next();
}
