#pragma once
#include <vector>
#include <map>
#include <string>
#include "Matchables/MatchableInterface.hpp"

class Result
{
public:
    Result();
    ~Result();

    vector<MatchableInterface *> getMatched();
    vector<MatchableInterface *> getNotMatched();
    map<string, vector<MatchableInterface *>> getOutputs();

    void setMatched(const vector<MatchableInterface *> &matches);
    void setNotMatched(const vector<MatchableInterface *> &matches);
    void setOutputs(const map<string, vector<MatchableInterface *>> &outputs);

protected:
    vector<MatchableInterface *> matched, notMatched;
    map<string, vector<MatchableInterface *>> outputs;
};
