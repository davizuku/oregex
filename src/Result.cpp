#include "Result.hpp"

using namespace std;

Result::Result(int index)
{
    lastMatchedIndex = index;
    setOutputs(map<string, forward_list<MatchableInterface *>>());
}

Result::Result(int index, const map<string, forward_list<MatchableInterface *>> &outputs)
{
    lastMatchedIndex = index;
    setOutputs(outputs);
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

ostream& operator<<(ostream &out, const Result &r)
{
    out << "Result(" << r.getLastMatchedIndex() << ", {" << endl;
    auto outputs = r.getOutputs();
    for (auto it = outputs.begin(); it != outputs.end(); ++it) {
        out << "\t\"" << it->first << "\": [";
        for (MatchableInterface* m: it->second) {
            out << m->getValue() << ", ";
        }
        out << "]" << endl;
    }
    out << "})" << endl;
    return out;
}
