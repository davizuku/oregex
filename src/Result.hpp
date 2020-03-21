#pragma once
#include <forward_list>
#include <vector>
#include <map>
#include <string>
#include <ostream>
#include "Matchables/MatchableInterface.hpp"

using namespace std;

class Result
{
public:
    Result();
    Result(size_t index);
    Result(size_t index, const map<string, forward_list<MatchableInterface *>> &outputs);
    ~Result();

    bool operator!=(const Result& other) const;
    bool operator==(const Result& other) const;

    int getLastMatchedIndex() const;
    map<string, forward_list<MatchableInterface *>> getOutputs() const;

    void setOutputs(const map<string, forward_list<MatchableInterface *>> &outputs);

    friend ostream& operator<<(ostream& out, const Result& r);

protected:
    int lastMatchedIndex;
    map<string, forward_list<MatchableInterface *>> outputs;
};
