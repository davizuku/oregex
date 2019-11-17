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
    while (not matchables.empty()) {
        MatchableInterface* m = matchables.front();
        consumed.push_front(m);
        matchables.pop_front();
        if (m->getValue() == value) {
            break;
        }
    }
    consumed.reverse();
    Result r;
    r.setConsumed(consumed);
    r.setPending(matchables);
    return r;
}
