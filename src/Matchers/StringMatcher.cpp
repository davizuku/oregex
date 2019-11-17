#include <string>
#include <forward_list>
#include "../Result.hpp"
#include "../Matchables/MatchableInterface.hpp"
#include "StringMatcher.hpp"

using namespace std;

StringMatcher::StringMatcher(string s)
{
    value = s;
}

StringMatcher::~StringMatcher()
{
}

Result StringMatcher::match(forward_list<MatchableInterface*> matchables)
{
    forward_list<MatchableInterface*> consumed = {};
    auto iter = consumed.before_begin();
    while (not matchables.empty()) {
        MatchableInterface* m = matchables.front();
        iter = consumed.insert_after(iter, m);
        matchables.pop_front();
        if (m->getValue() == value) {
            break;
        }
    }
    Result r;
    r.setConsumed(consumed);
    r.setPending(matchables);
    return r;
}
