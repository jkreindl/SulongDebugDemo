# Sulong Debugging Demo - Postfix Expression Calculator as a Standalone C-Program

This code implements a tool for evaluating simple arithmetic expressions in [postfix notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation). It is implemented entirely in C and intended to demonstrate source-level and IR-level debugging of C-programs compiled to LLVM-IR with GraalVM.

## EuroLLVM

This demo was shown at the EuroLLVM 2019 in Brussels, Belgium. All features shown are already available in GraalVM RC15, but some bugfixes will only be available in GraalVM RC16.

## Usage

The demo evaluates a hard-coded arithmetic expression in postfix notation. The operands are of the following kinds:

* signed integer numbers: these will be pushed onto the internal number stack
* `+`, `-`, `*`, `/`: these pop the top two values from the internal number stack, perform the operation, and push the result back onto the stack
* `=`: prints the current content of the internal number stack top-down

## Getting started

This demo provides a Makefile for compiling the C code to LLVM bitcode that Sulong can execute.

    make

You can then run the demo and debug the code in the Chrome Devtools.

### Source-Level Debugging

In order to debug the program at source level please make sure that it is compiled with debug information. You can use the provided Makefile to ensure this.

    make clean
    make

You can then use the following command to debug the program at source-level.

    $GRAALVM/bin/lli \
        --experimental-options \
        --llvm.enableLVI=true \
        --llvm.lazyParsing=false \
        --inspect \
        calc.bc

This will print a URL to the console. Enter that URL into Chrome's address bar to start debugging.

### IR-Level Debugging with Managed Sulong

In order to debug the program at IR-level please make sure that for each executed `.bc`-file there is an appropriate `.ll`-file with the corresponding disassembled bitcode. You can use the provided Makefile to ensure this.

    make clean
    NO_DEBUG=true make

You can use the following command to debug the program at IR-level.

    $GRAALVM/bin/lli
        --experimental-options \
        --llvm.llDebug=true \
        --llvm.lazyParsing=false \
        --inspect \
        calc.bc

This will print a URL to the console. Enter that URL into Chrome's address bar to start debugging.

### Sandboxed Mode

In order to be able to dereference arbitrary pointers when debugging you can enable sandboxed mode by adding the `--llvm.sandboxed`. However, this feature is only available in GraalVM Enterprise Edition.

Please note that, due to a bug in Sulong, you currently cannot use sandboxed mode together with the `--llvm.lazyParsing=false` option.
