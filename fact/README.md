# Sulong Debugging Demo - Factorial as a Ruby C-Extension

This code implements the factorial function in C and uses it as C-extension for a ruby program. It is intended to demonstrate cross-language debugging with GraalVM.

## Getting started

This demo provides the Ruby program [`extconf.rb`](extconf.rb) to generate a Makefile for compiling the C code. Please make sure to execute it only on TruffleRuby.

    $GRAALVM/bin/ruby extconf.rb
    make

This compiles the C extension to LLVM bitcode that Sulong can execute. You can then run the demo and debug the code in the Chrome Devtools.

    $GRAALVM/bin/ruby --llvm.enableLVI=true --llvm.lazyParsing=false --inspect fact.rb

This should print a URL to the console. Enter that URL into Chrome's address bar to start debugging.
