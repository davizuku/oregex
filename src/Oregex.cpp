#include "Oregex.hpp"
#include "Result.hpp"
#include "Matchers/GroupMatcher.hpp"

Oregex::Oregex(const vector<MatcherInterface *> &matchers)
{
    matcher = new GroupMatcher(matchers);
}

Oregex::~Oregex()
{
}

bool Oregex::match(vector<MatchableInterface *> &matchables)
{
    map<string, forward_list<MatchableInterface *>> outputs;
    return match(matchables, outputs);
}

void buildOutputs(
    map<string, forward_list<MatchableInterface *>> &outputs,
    const forward_list<Result> &results
) {
    for (const Result &r: results) {
        auto rOuts = r.getOutputs();
        for (auto it = rOuts.begin(); it != rOuts.end(); ++it) {
            bool hasKey = outputs.find(it->first) != outputs.end();
            if (not hasKey) {
                outputs[it->first] = it->second;
            }
        }
    }
}

bool Oregex::match(
    vector<MatchableInterface *> &matchables,
    map<string, forward_list<MatchableInterface *>> &outputs
) {
    for (int i = 0; i < matchables.size(); ++i) {
        auto results = matcher->match(matchables, i);
        if (not results.empty()) {
            buildOutputs(outputs, results);
            return true;
        }
    }
    return false;
}
