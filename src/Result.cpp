#include "Result.hpp"

Result::Result(int index)
{
    lastMatchedIndex = index;
    setOutputs(map<string, forward_list<MatchableInterface *>>());
}

Result::~Result()
{
}

bool Result::operator!=(const Result &other) const
{
    return getLastMatchedIndex() != other.getLastMatchedIndex();
}

bool Result::operator==(const Result &other) const
{
    return getLastMatchedIndex() == other.getLastMatchedIndex();
}

int Result::getLastMatchedIndex() const
{
    return lastMatchedIndex;
}

map<string, forward_list<MatchableInterface *>> Result::getOutputs() const
{
    return outputs;
}

void Result::setOutputs(const map<string, forward_list<MatchableInterface *>> &outs)
{
    outputs = outs;
}
