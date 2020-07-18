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

bool Oregex::match(
    vector<MatchableInterface *> &matchables,
    unordered_map<string, forward_list<MatchableInterface *>> &outputs
) {
    for (size_t i = 0; i < matchables.size(); ++i) {
        Result* r = matcher->match(matchables, i);
        if (r != NULL) {
            outputs = r->getOutputs();
            delete r;
            return true;
        }
    }
    return false;
}
