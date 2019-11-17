#include <forward_list>
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

forward_list<MatchableInterface*> Result::getConsumed()
{
    return consumed;
}

forward_list<MatchableInterface*> Result::getPending()
{
    return pending;
}

map<string, forward_list<MatchableInterface*> > Result::getOutputs()
{
    return outputs;
}

void Result::setConsumed(const forward_list<MatchableInterface*> &matches)
{
    consumed = matches;
}

void Result::setPending(const forward_list<MatchableInterface*> &matches)
{
    pending = matches;
}

void Result::setOutputs(const map<string, forward_list<MatchableInterface*> > &outs)
{
    outputs = outs;
}
