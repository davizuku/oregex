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

vector<MatchableInterface*> Result::getMatched()
{
    return matched;
}

vector<MatchableInterface*> Result::getNotMatched()
{
    return notMatched;
}

map<string, vector<MatchableInterface*> > Result::getOutputs()
{
    return outputs;
}

void Result::setMatched(const vector<MatchableInterface*> &matches)
{
    matched = matches;
}

void Result::setNotMatched(const vector<MatchableInterface*> &matches)
{
    notMatched = matches;
}

void Result::setOutputs(const map<string, vector<MatchableInterface*> > &outs)
{
    outputs = outs;
}
