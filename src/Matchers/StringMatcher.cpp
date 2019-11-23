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

forward_list<Result> StringMatcher::match(
    vector<MatchableInterface *> matchables,
    int start
) {
    forward_list<Result> results;
    int n = matchables.size();
    for (int i = start; i < n; ++i) {
        MatchableInterface *m = matchables[i];
        if (m->getValue() == value) {
            results.push_front(Result(i));
            break;
        }
    }
    return results;
}
