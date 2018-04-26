# Sulong Debugging Demo - Evaluate Arithmetic Expressions in Postfix Notation

This is a tool for evaluating simple arithmetic expressions in [postfix notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation). It uses Ruby code to parse the given expression and a C++ extension for Ruby to compute its result.

## Getting started

This demo provides the Ruby program [`extconf.rb`](extconf.rb) to generate a Makefile for compiling the C++ code. Please make sure to execute it only on TruffleRuby.

    $GRAALVM/bin/ruby extconf.rb
    make

This compiles the C++ extension to LLVM bitcode that Sulong can execute. You can then run the demo and debug the code in the Chrome Devtools.

    $GRAALVM/bin/ruby --llvm.enableLVI=true --inspect calc.rb <expression>

This should print a URL to the console. Enter that URL into Chrome's address bar to start debugging.
