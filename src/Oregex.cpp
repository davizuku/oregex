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
    for (int i = 0; i < matchables.size(); ++i) {
        if (not matcher->match(matchables, i).empty()) {
            return true;
        }
    }
    return false;
}
