#pragma once
#include <vector>
#include "Matchers/MatcherInterface.hpp"
#include "Matchables/MatchableInterface.hpp"

class Oregex
{
public:
    Oregex(const vector<MatcherInterface *> &matchers);
    ~Oregex();

    bool match(vector<MatchableInterface *> &matchables);
    bool match(
        vector<MatchableInterface *> &matchables,
        unordered_map<string, forward_list<MatchableInterface *>> &outputs
    );

protected:
    vector<MatcherInterface*> matchers;
};
