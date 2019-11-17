#include <string>
#include <vector>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"
#include "StringMatcher.hpp"
#include <iostream>

using namespace std;

StringMatcher::StringMatcher(string s)
{
    value = s;
}

StringMatcher::~StringMatcher()
{
}

Result StringMatcher::match(vector<MatchableInterface *> matchables)
{
    vector<MatchableInterface*> consumed, pending;
    int n = matchables.size();
    bool matched = false;
    for (int i = 0; i < n; ++i) {
        MatchableInterface* m = matchables[i];
        if (not matched) {
            consumed.push_back(m);
            matched = m->getValue() == value;
        } else {
            pending.push_back(m);
        }
    }
    Result r;
    r.setConsumed(consumed);
    r.setPending(pending);
    return r;
}
