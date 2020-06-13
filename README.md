# oregex

C++ Library to create regular expressions with customized elements

## Introduction

## Operators

### WIP overview

- :white_check_mark: Implemented: 8
- :warning: Alternative: 2
- :x: Not implemented: 11

### Details

|Status|Operator|Description|Examples|
|--------|-----------|--------|------|
|[:white_check_mark:](https://github.com/davizuku/oregex/blob/master/src/Matchers/StarMatcher.hpp)|Start|Matches the start of a sequence|`abc` -> `/^abc/` :white_check_mark:<br>`abc` -> `/^bcd/` :x: |
|[:white_check_mark:](https://github.com/davizuku/oregex/blob/master/src/Matchers/EndMatcher.hpp)|End|Matches the end of a sequence|`abc` -> `/abc$/` :white_check_mark:<br>`abc` -> `/bcd$/` :x:|
|:x:|Any|Matches any element|`abc` -> `/./` :white_check_mark:<br>` ` -> `/./` :x:|
|[:white_check_mark:](https://github.com/davizuku/oregex/blob/master/src/Matchers/GroupMatcher.hpp)|Group|Matches a sequence of elements|`abc` -> `/(abc)/` :white_check_mark:<br>`acb` -> `/(abc)/` :x:|
|[:white_check_mark:](https://github.com/davizuku/oregex/blob/master/src/Matchers/NamedGroupMatcher.hpp)|NamedGroup|Matches a sequence of elements and outputs it under the given name|`abc` -> `/(?<name>abc)/` :white_check_mark:<br>`acb` -> `/(?<name>abc)/` :x:|
|[:white_check_mark:](https://github.com/davizuku/oregex/blob/master/src/Matchers/OrMatcher.hpp)|Or|Matches any element from a list|`abc` -> `/(xyz\|abc)/` :white_check_mark:<br>`abc` -> `/(npm\|xyz)/` :x:|
|:x:|Except|Matches any element except for those in a list|`abc` -> `/[^xyz]+/` :white_check_mark:<br>`abc` -> `/[^abc]+/` :x:|
|:x:|Again|Matches the elements previously matched in a group|`abc abc` -> `/(?<first>abc) (\k<first>)/` :white_check_mark:<br>`abc efg` -> `/(?<first>abc) (\k<first>)/` :x:<br>`abc abc` -> `/(abc) (\g<1>)/` :white_check_mark:<br>`abc efg` -> `/(abc) (\g<1>)/` :x:|
|:x:|PositiveLookAhead|Matches the elements in list without consuming the input.| `abc` -> `/a(?=bc)bc/` :white_check_mark:<br>`acb` -> `/a(?=bc)bc/` :x:|
|:x:|NegativeLookAhead|Checks not match with the elements in list without consuming the input.| `abc` -> `/a(?!cb)bc/` :white_check_mark:<br>`acb` -> `/a(?!cb)cb/` :x:|
|:x:|PositiveLookBehind|Matches the elements in list without consuming the input.| `abc` -> `/(?<=bc)abc/` :white_check_mark:<br>`abc` -> `/(?<=a)abc/` :x:|
|:x:|NegativeLookBehind|Checks not match with the elements in list without consuming the input.| `abc` -> `/(?<!cb)abc/` :white_check_mark:<br>`abc` -> `/(?<!bc)abc/` :x:|
|:x:|Condition|Matches the elements in seqTrue if group was matched, seqFalse otherwise.| `abc xyz` -> `/(abc)? (?(1)xyz\|opq)/` :white_check_mark:<br>`acb opq` -> `/(abc)? (?(1)xyz\|opq)/` :x:|
|:x:|ConditionalLookAhead|Matches the elements in seqTrue if seqLook matches, seqFalse otherwise.| `abc xyz` -> `/(?(?=a)(abc)\|(cba))/` :white_check_mark:<br>`xyz cba` -> `/(?(?=a)(abc)\|(cba))/` :x:|
|:x:|ConditionalLookBehind|Matches the elements in seqTrue if seqLook matches, seqFalse otherwise.| `abc xyz` -> `/(?(?<=abc )(xyz)\|(cba))/` :white_check_mark:<br>`xyz cba` -> `/(?(?<=abc )(xyz)\|(cba))/` :x:|
|[:warning:](https://github.com/davizuku/oregex/blob/master/src/Matchers/RangeMatcher.hpp)|Optional|Matches zero or one occurrence of an element| `a` -> `/ab?/` :white_check_mark:|
|[:white_check_mark:](https://github.com/davizuku/oregex/blob/master/src/Matchers/StarMatcher.hpp)|Star|Matches zero or more occurences of an element|`aaaaa` -> `/a*/` :white_check_mark:|
|[:warning:](https://github.com/davizuku/oregex/blob/master/src/Matchers/RangeMatcher.hpp)|Plus|Matches one or more occurences of an element|`aaaaa` -> `/a+/` :white_check_mark:<br>`bbbb` -> `/a+/` :x:|
|[:white_check_mark:](https://github.com/davizuku/oregex/blob/master/src/Matchers/ExactlyMatcher.hpp)|Exactly|Matches exact number of occurrences of an element|`aaa` -> `/a{3}/` :white_check_mark:<br>`aa` -> `/a{3}/` :x:|
|[:white_check_mark:](https://github.com/davizuku/oregex/blob/master/src/Matchers/RangeMatcher.hpp)|Range|Matches a number of occurrences of an element between min and max|`aaa` -> `/a{1,3}/` :white_check_mark:<br>`aa` -> `/a{3, 5}/` :x:|
|:x:|Lazy/Ungreedy|Makes an operator consume as few input as possible|`aaa` -> `/a*?/` :white_check_mark: (will only match first 'a')|


Source: regex101.com

## Useful commands

```
make test
```

## Help links

- http://www.cplusplus.com/reference/
- https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/GCC/create-libraries/index
- https://github.com/eocron/ORegex
- https://www.npmjs.com/package/oregex/v/1.0.2


## Developed in vscode for Mac OS X

- https://code.visualstudio.com/docs/cpp/config-clang-mac
- https://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile
