# Sulong Debugging Demo - Postfix Expression Calculator as a Standalone C-Program

This code implements a tool for evaluating simple arithmetic expressions in [postfix notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation). It is implemented entirely in C and intended to demonstrate source-level and IR-level debugging of C-programs compiled to LLVM-IR with GraalVM.

## Usage

The demo evaluates a hard-coded arithmetic expression in postfix notation. The operands are the following:

* signed integer numbers: these will be pushed onto the internal number stack
* `+`, `-`, `*`, `/`: these pop the top two values from the internal number stack, perform the operation, and push the result back onto the stack
* `=`: prints the current content of the internal number stack top-down

## Getting started

This demo provides a Makefile for compiling the C code to LLVM IR.

    make

This compiles the C extension to LLVM bitcode that Sulong can execute. You can then run the demo and debug the code in the Chrome Devtools.

### Source-Level Debugging with Native Sulong

You can use the following command to debug the program at source-level using native Sulong, which is available in both the Community Edition and the Enterprise Edition of GraalVM.

    $GRAALVM/bin/lli --llvm.enableLVI=true --llvm.lazyParsing=false --inspect calc.bc 1 2 3 = + +

This will print a URL to the console. Enter that URL into Chrome's address bar to start debugging.

### Source-Level Debugging with Managed Sulong

You can use the following command to debug the program at source-level using managed Sulong, which is available only in the Enterprise Edition of GraalVM. Compared to debugging with native Sulong, managed Sulong also enables you to safely inspect the targets of pointer values.

    $GRAALVM/bin/lli --llvm.enableLVI=true --llvm.lazyParsing=false --inspect --llvm.sandboxed=true calc.bc 1 2 3 = + +

This will print a URL to the console. Enter that URL into Chrome's address bar to start debugging.

### IR-Level Debugging with Managed Sulong

You can use the following command to debug the program at IR-level using managed Sulong, which is available only in the Enterprise Edition of GraalVM. Compared to debugging with native Sulong, managed Sulong also enables you to safely inspect the targets of pointer values.

    $GRAALVM/bin/lli --llvm.llDebug=true --llvm.lazyParsing=false --inspect --llvm.sandboxed=true calc.bc 1 2 3 = + +

This will print a URL to the console. Enter that URL into Chrome's address bar to start debugging.
