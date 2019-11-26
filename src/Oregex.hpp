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

protected:
    vector<MatcherInterface *> matchers;
};
