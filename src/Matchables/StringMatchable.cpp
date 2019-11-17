#include <string>
#include "StringMatchable.hpp"

using namespace std;

StringMatchable::StringMatchable(string s)
{
    value = s;
}

StringMatchable::~StringMatchable()
{
}

string StringMatchable::getValue()
{
    return value;
}
