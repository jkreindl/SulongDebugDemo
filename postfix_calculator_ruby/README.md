# Sulong Debugging Demo - Postfix Expression Calculator as a Ruby C-Extension

This code implements a tool for evaluating simple arithmetic expressions in [postfix notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation). It implements the calculator in C and uses it as C-extension for a ruby program. It is intended to demonstrate cross-language debugging with GraalVM.

## Usage

The demo takes an arithmetic expression in postfix notation as argument. Valid operands are the following:

* signed integer numbers: these will be pushed onto the internal number stack
* `+`, `-`, `*`, `/`: these pop the top two values from the internal number stack, perform the operation, and push the result back onto the stack
* `=`: prints the current content of the internal number stack top-down

## Getting started

This demo provides the Ruby program [`extconf.rb`](extconf.rb) to generate a Makefile for compiling the C code. Please make sure to execute it only on TruffleRuby.

    $GRAALVM/bin/ruby extconf.rb
    make

This compiles the C extension to LLVM bitcode that Sulong can execute. You can then run the demo and debug the code in the Chrome Devtools.

    $GRAALVM/bin/ruby \
        --llvm.enableLVI=true \
        --llvm.lazyParsing=false \
        --inspect \
        calc.rb \
        1 2 3 = + +

This should print a URL to the console. Enter that URL into Chrome's address bar to start debugging.
