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
    this->matchables = matchables;
    this->start = start;
    this->previousResults = previousResults;
    this->curResult = previousResults.before_begin();
    return next();
}

Result* AgainMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return NULL;
}

Result* AgainMatcher::next()
{
    if (curResult != previousResults.end()) {
        curResult++;
    }
    if (curResult == previousResults.end()) {
        return NULL;
    }
    auto outputs = curResult->getOutputs();
    auto repeatOutput = outputs.find(outputName);
    if (repeatOutput != outputs.end()) {
        auto repeatMatchables = repeatOutput->second;
        size_t k = start;
        forward_list<MatchableInterface*>::iterator j;
        for (j = repeatMatchables.begin(); j != repeatMatchables.end() && k < matchables.size(); ++j) {
            MatchableInterface *m1 = matchables[k++];
            MatchableInterface *m2 = *j;
            if (m1->getValue() != m2->getValue()) {
                break;
            }
        }
        if (j == repeatMatchables.end()) {
            return new Result(start, max(start, k - 1));
        }
    }
    return next();
}
