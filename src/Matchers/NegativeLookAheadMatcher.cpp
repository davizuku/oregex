#include "NegativeLookAheadMatcher.hpp"
#include "ExceptMatcher.hpp"

NegativeLookAheadMatcher::NegativeLookAheadMatcher(MatcherInterface *matcher) :
    PositiveLookAheadMatcher(new ExceptMatcher(vector<MatcherInterface *>{matcher})) {}

NegativeLookAheadMatcher::~NegativeLookAheadMatcher() {}
