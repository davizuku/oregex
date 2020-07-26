#include "NamedGroupMatcher.hpp"

NamedGroupMatcher::NamedGroupMatcher(string n, MatcherInterface *m)
{
    name = n;
    matcher = m;
    results = queue<Result*>();
}

NamedGroupMatcher::~NamedGroupMatcher()
{
    while (not results.empty()) {
        Result* r = results.front();
        results.pop();
        delete r;
    }
}

Result* NamedGroupMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    results = queue<Result*>();
    Result* r = matcher->match(matchables, start, previousResults);
    while (r != NULL) {
        size_t end = r->getLastMatchedIndex();
        auto subOutputs = r->getOutputs();
        forward_list<MatchableInterface *> outputList;
        outputList.insert_after(
            outputList.before_begin(),
            matchables.begin() + start,
            matchables.begin() + end + 1
        );
        subOutputs[name] = outputList;
        results.push(new Result(
            r->getFirstMatchedIndex(),
            end,
            subOutputs
        ));
        r = matcher->next();
    }
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
    if (results.empty()) {
        return NULL;
    }
    Result* r = results.front();
    results.pop();
    return r;
}
