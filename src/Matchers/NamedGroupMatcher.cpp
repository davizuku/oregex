#include "NamedGroupMatcher.hpp"

NamedGroupMatcher::NamedGroupMatcher(string n, MatcherInterface *m)
{
    name = n;
    matcher = m;
}

NamedGroupMatcher::~NamedGroupMatcher()
{
    for (auto it = results.begin(); it != results.end(); ++it) {
        delete *it;
    }
}

Result* NamedGroupMatcher::match(
    const vector<MatchableInterface *> &matchables,
    size_t start,
    const forward_list<Result> &previousResults
) {
    results = list<Result*>{};
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
        results.push_back(new Result(
            r->getFirstMatchedIndex(),
            end,
            subOutputs
        ));
        r = matcher->next();
    }
    resultIt = results.begin();
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
    if (resultIt == results.end()) {
        return NULL;
    }
    Result* r = *resultIt;
    resultIt++;
    return r;
}
