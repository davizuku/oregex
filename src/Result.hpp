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

    vector<MatchableInterface *> getConsumed();
    vector<MatchableInterface *> getPending();
    map<string, vector<MatchableInterface *>> getOutputs();

    void setConsumed(const vector<MatchableInterface *> &matches);
    void setPending(const vector<MatchableInterface *> &matches);
    void setOutputs(const map<string, vector<MatchableInterface *>> &outputs);

protected:
    vector<MatchableInterface*> consumed, pending;
    map<string, vector<MatchableInterface*> > outputs;
};
