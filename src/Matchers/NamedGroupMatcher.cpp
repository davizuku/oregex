#include "NamedGroupMatcher.hpp"

NamedGroupMatcher::NamedGroupMatcher(string n, MatcherInterface *m)
{
    name = n;
    matcher = m;
}

NamedGroupMatcher::~NamedGroupMatcher()
{
}

Result* NamedGroupMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    results = forward_list<Result>{};
    forward_list<Result> subResults;
    Result* r = matcher->match(matchables, start, previousResults);
    while (r != NULL) {
        subResults.push_front(*r);
        r = matcher->next();
    }
    subResults.reverse();
    for (auto it = subResults.begin(); it != subResults.end(); it++) {
        int end = it->getLastMatchedIndex();
        auto subOutputs = it->getOutputs();
        Result r(end);
        forward_list<MatchableInterface *> outputList;
        outputList.insert_after(
            outputList.before_begin(),
            matchables.begin() + start,
            matchables.begin() + end + 1
        );
        subOutputs[name] = outputList;
        r.setOutputs(subOutputs);
        results.push_front(r);
    }
    results.reverse();
    lastResultIterator = results.before_begin();
    return next();
}

Result* NamedGroupMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start
) {
    return match(matchables, start, forward_list<Result>{});
}

Result* NamedGroupMatcher::next()
{
    ++lastResultIterator;
    if (lastResultIterator == results.end()) {
        return NULL;
    }
    return &(*lastResultIterator);
}
