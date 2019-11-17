#pragma once
#include <forward_list>
#include <map>
#include <string>
#include "Matchables/MatchableInterface.hpp"

class Result
{
public:
    Result();
    ~Result();

    forward_list<MatchableInterface *> getConsumed();
    forward_list<MatchableInterface *> getPending();
    map<string, forward_list<MatchableInterface *>> getOutputs();

    void setConsumed(const forward_list<MatchableInterface *> &matches);
    void setPending(const forward_list<MatchableInterface *> &matches);
    void setOutputs(const map<string, forward_list<MatchableInterface *>> &outputs);

protected:
    forward_list<MatchableInterface*> consumed, pending;
    map<string, forward_list<MatchableInterface*> > outputs;
};
