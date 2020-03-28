#include "Result.hpp"

Result::Result(
    size_t start,
    size_t end,
    const unordered_map<string, forward_list<MatchableInterface *>> &outputs
) {
    firstMatchedIndex = start;
    lastMatchedIndex = end;
    setOutputs(outputs);
}

Result::~Result()
{
}

bool Result::operator!=(const Result &other) const
{
    return not ((*this) == other);
}

bool Result::operator==(const Result &other) const
{
    return
        getFirstMatchedIndex() == other.getFirstMatchedIndex() and
        getLastMatchedIndex() == other.getLastMatchedIndex() and
        getOutputs() == other.getOutputs();
}

int Result::getFirstMatchedIndex() const
{
    return firstMatchedIndex;
}

int Result::getLastMatchedIndex() const
{
    return lastMatchedIndex;
}

unordered_map<string, forward_list<MatchableInterface *>> Result::getOutputs() const
{
    return outputs;
}

void Result::setOutputs(const unordered_map<string, forward_list<MatchableInterface *>> &outs)
{
    outputs = outs;
}

ostream& operator<<(ostream &out, const Result &r)
{
    out << "Result(" << r.getLastMatchedIndex() << ", {";
    auto outputs = r.getOutputs();
    for (auto it = outputs.begin(); it != outputs.end(); ++it) {
        out << "\"" << it->first << "\": [";
        for (MatchableInterface* m: it->second) {
            out << "'" << m->getValue() << "', ";
        }
        out << "], ";
    }
    out << "})";
    return out;
}
