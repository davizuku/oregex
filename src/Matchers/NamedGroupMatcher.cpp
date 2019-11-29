#include "NamedGroupMatcher.hpp"

NamedGroupMatcher::NamedGroupMatcher(string n, MatcherInterface *m)
{
    name = n;
    matcher = m;
}

NamedGroupMatcher::~NamedGroupMatcher()
{
}

forward_list<Result> NamedGroupMatcher::match(
    const vector<MatchableInterface *> &matchables,
    int start,
    const forward_list<Result> &previousResults
) {
    forward_list<Result> results, subResults = matcher->match(
        matchables,
        start,
        previousResults
    );
    for (auto it = subResults.begin(); it != subResults.end(); it++) {
        int end = it->getLastMatchedIndex();
        Result r(end);
        forward_list<MatchableInterface *> outputList;
        outputList.insert_after(
            outputList.before_begin(),
            matchables.begin() + start,
            matchables.begin() + end + 1
        );
        r.setOutputs(map<string, forward_list<MatchableInterface *>>{
            {name, outputList}
        });
        results.push_front(r);
    }
    results.reverse();
    return results;
}

forward_list<Result> NamedGroupMatcher::match(
    const vector<MatchableInterface *> &matchables,
    int start
) {
    return match(matchables, start, forward_list<Result>{});
}
