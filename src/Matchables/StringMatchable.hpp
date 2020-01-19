#pragma once
#include <string>
#include "MatchableInterface.hpp"

using namespace std;

class StringMatchable: public MatchableInterface
{
    public:
        StringMatchable(string s);
        ~StringMatchable();

        string getValue() const;

    protected:
        string value;
};
