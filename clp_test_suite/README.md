# clp_test_suite
C Lexer and Parser test suite

# Setting up

You'll need the following programs:

* `meson`
* `ninja`
* A C compiler
* A C++ compiler
* Google Test

There is a package on the AUR for the dev version of gtest. Regarding `meson` and
`ninja`, they're available via `pacman`.

# Execution

```
meson build
cd build
ninja test
```

will build and run the tests.

# Implementation

The headers you need to implement are in `include/`. You need to implement
the files in a directory called `src`.

Look at the meson.build file, in the src array, in order to get the exact
names and location.

You can comment out tests in tests by putting a # in front of the test name.
This way, you do not have to implement everything at once

There isn't anything to implement in `tokens.h`.

I suggest implementing the token vector, the lexer and then the parser
