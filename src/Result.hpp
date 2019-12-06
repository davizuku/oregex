#pragma once
#include <forward_list>
#include <vector>
#include <map>
#include <string>
#include "Matchables/MatchableInterface.hpp"

class Result
{
public:
    Result();
    Result(int index);
    ~Result();

    bool operator!=(const Result& other) const;
    bool operator==(const Result& other) const;

    int getLastMatchedIndex() const;
    map<string, forward_list<MatchableInterface *>> getOutputs() const;

    void setOutputs(const map<string, forward_list<MatchableInterface *>> &outputs);

protected:
    int lastMatchedIndex;
    map<string, forward_list<MatchableInterface *>> outputs;
};
