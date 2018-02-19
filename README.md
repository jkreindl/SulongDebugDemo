# Sulong Debugging Demo

This is a sample project to demonstrate cross-language debugging of C and Ruby code using [Sulong](https://github.com/graalvm/sulong) and [TruffleRuby](https://github.com/oracle/truffleruby). Both language implementations are part of the [GraalVM](http://www.oracle.com/technetwork/oracle-labs/program-languages/overview/index.html) project.

## About the demo

This is a simple tool for computing all satisfying assignments for a boolean formula given in [the Boole Language](http://fmv.jku.at/limboole/README) defined by [Limboole](http://fmv.jku.at/limboole/). It uses the versatility of Ruby to read and tokenize the input files and the performance and safety of C to build up and evaluate an AST representing the formula.

## Prerequisites

Please ensure that you have Clang and LLVM, including the `opt` tool available on your path. For a list of compatible versions please check [the Sulong README](https://github.com/graalvm/sulong). If you are using a version of Clang earlier than 5.0 please comment out the line `CLANG_ARGS=-Xclang -disable-O0-optnone` in the [Makefile](Makefile).

## Getting started

You can download the [latest GraalVM release from Oracle](http://www.oracle.com/technetwork/oracle-labs/program-languages/downloads/index.html).

To compile the C code of this demo please use the provided Makefile.

    make

This should give you a file `c_boole.bc`, containing the LLVM bitcode to execute with Sulong. To debug the program for the [provided examples](tests) with GraalVM's Chrome Inspector you can use this command:

    GRAALVM/bin/polyglot --file c_boole.bc --llvm.enableLVI=true --inspect bool_eval.rb $(find tests/ -name '*.boole')

This should print a URL to the console. Enter that URL into Chrome's address bar to start debugging.
