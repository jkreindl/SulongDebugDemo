# Sulong Debugging Demo - Evaluate Boolean Formulae

This is a simple tool for computing all satisfying assignments for a boolean formula given in [the Boole Language](http://fmv.jku.at/limboole/README) defined by [Limboole](http://fmv.jku.at/limboole/). It uses the versatility of Ruby to read and tokenize the input files and the performance and safety of C to build up and evaluate an AST representing the formula.

## Getting started

To compile the C code of this demo please use the provided Makefile. If you are using a version of Clang earlier than 5.0 please comment out the line `CLANG_ARGS=-Xclang -disable-O0-optnone` in the [Makefile](Makefile).

    make

This should give you a file `c_boole.bc`, containing the LLVM bitcode to execute with Sulong. To debug the program for the [provided examples](tests) with GraalVM's Chrome Inspector you can use this command:

    $GRAALVM/bin/polyglot --file c_boole.bc --llvm.enableLVI=true --inspect bool_eval.rb $(find tests/ -name '*.boole')

This should print a URL to the console. Enter that URL into Chrome's address bar to start debugging.
