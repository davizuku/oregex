#pragma once
#include <forward_list>
#include <vector>
#include <unordered_map>
#include <string>
#include <ostream>
#include "Matchables/MatchableInterface.hpp"

using namespace std;

class Result
{
public:
    Result(): Result(-1, -1){};
    Result(size_t start, size_t end): Result(start, end, {}){};
    Result(
        size_t start,
        size_t end,
        const unordered_map<string, forward_list<MatchableInterface *>> &outputs
    );
    ~Result();

    bool operator!=(const Result& other) const;
    bool operator==(const Result& other) const;

    int getFirstMatchedIndex() const;
    int getLastMatchedIndex() const;
    unordered_map<string, forward_list<MatchableInterface *>> getOutputs() const;

    void setOutputs(const unordered_map<string, forward_list<MatchableInterface *>> &outputs);

    friend ostream& operator<<(ostream& out, const Result& r);

protected:
    int firstMatchedIndex;
    int lastMatchedIndex;
    unordered_map<string, forward_list<MatchableInterface *>> outputs;
};
