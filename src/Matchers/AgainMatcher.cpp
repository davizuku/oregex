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
    for (auto i = previousResults.begin(); i != previousResults.end(); ++i) {
        auto outputs = i->getOutputs();
        auto repeatOutput = outputs.find(outputName);
        if (repeatOutput != outputs.end()) {
            auto repeatMatchables = repeatOutput->second;
            size_t k = start;
            for (auto j = repeatMatchables.begin(); j != repeatMatchables.end() && k < matchables.size(); ++j) {
                MatchableInterface* m1 = matchables[k++];
                MatchableInterface* m2 = *j;
                if (m1->getValue() != m2->getValue()) {
                    // TODO: edit this for next()
                    return NULL;
                }
            }
            return new Result(start, max(start, k-1));
        }
    }
    return NULL;
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
