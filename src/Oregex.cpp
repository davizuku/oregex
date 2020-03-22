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
    unordered_map<string, forward_list<MatchableInterface *>> outputs;
    return match(matchables, outputs);
}

void buildOutputs(
    unordered_map<string, forward_list<MatchableInterface *>> &outputs,
    const list<Result*> &results
) {
    for (const Result* r: results) {
        auto rOuts = r->getOutputs();
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
    unordered_map<string, forward_list<MatchableInterface *>> &outputs
) {
    for (size_t i = 0; i < matchables.size(); ++i) {
        list<Result*> results;
        Result* r = matcher->match(matchables, i);
        while (r != NULL) {
            results.push_back(r);
            r = matcher->next();
        }
        if (not results.empty()) {
            buildOutputs(outputs, results);
            return true;
        }
    }
    return false;
}
