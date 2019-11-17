#include <vector>
#include <map>
#include <string>
#include "Matchables/MatchableInterface.hpp"
#include "Result.hpp"

Result::Result()
{
}

Result::~Result()
{
}

vector<MatchableInterface*> Result::getConsumed()
{
    return consumed;
}

vector<MatchableInterface*> Result::getPending()
{
    return pending;
}

map<string, vector<MatchableInterface*> > Result::getOutputs()
{
    return outputs;
}

void Result::setConsumed(const vector<MatchableInterface*> &matches)
{
    consumed = matches;
}

void Result::setPending(const vector<MatchableInterface*> &matches)
{
    pending = matches;
}

void Result::setOutputs(const map<string, vector<MatchableInterface*> > &outs)
{
    outputs = outs;
}
