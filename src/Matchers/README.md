# Matcher Documentation

## What is a Matcher?

As stated in the main README:

> A [`Matcher`](src/Matchers/MatcherInterface.hpp) is an operator capable of consuming a set of `Matchables` from the input sequence and returning a [`Result`](src/../../Result.hpp). Depending on their logic they could match different amount of elements.

Every `Matcher` returns the greediest [`Result`](src/Result.hpp) on the first call to `match(...)` method. Consecutive less greedy results can be obtained using the `next()` method on the same matcher.

## What does a `Result` look like?

As the output of the matching process a `Result` is generated. This object contains all the necessary information for `Oregex` to keep track of the whole process. This information includes:
- `start`: the initial index from the input sequence that the `Matcher` has consumed to build the `Result`.
- `end`: the final index from the input sequence that the `Matcher` has consumed while building the `Result`. This index has to be understood as _inclusive_, i.e. the element in the index `end` must be included in the scope of the `Result`.
- `outputs`: If the `Matcher` builds a named group of the input sequence, it will be specified in this property. It is a map/dictionary that relates `string => Matchable[]`.

If the `Matcher` does not match `NULL` is returned as a `Result`.

Some examples, assuming `ColorMatchers` only match with _background_ color of shapes:

![result-examples](../../img/result-examples.png)
